#include "Field.h"
#include "Asset.h"
#include "GameConstants.h"
#include "GameSceneDirector.h"

static const TVec3f SKY_POSITION[Field::DIRECTION_DATANUM] =
{
  { 0.0f, 0.0f,-1.0f },
  {-1.0f, 0.0f, 0.0f },
  { 0.0f, 0.0f, 1.0f },
  { 1.0f, 0.0f, 0.0f },
};

static const T_FLOAT SKY_ROTATION[Field::DIRECTION_DATANUM] =
{
  180.0f,
  -90.0f,
  0.0f,
  90.0f
};

static const Color4F SKY_BASE_COLOR[GameConstants::PHASE_DATANUM + 1] =
{
  Color4F::CreateBy4BitFormat(120, 150, 200),
  Color4F::CreateBy4BitFormat(100, 24, 29),
  Color4F::CreateBy4BitFormat(0, 0, 36),
  Color4F::CreateBy4BitFormat(0, 0, 10),
  Color4F::CreateBy4BitFormat(0, 0, 0),
};

static const Color4F SKY_FADE_COLOR[GameConstants::PHASE_DATANUM + 1] =
{
  Color4F::CreateBy4BitFormat(0, 169, 255),
  Color4F::CreateBy4BitFormat(64, 28, 0),
  Color4F::CreateBy4BitFormat(0, 12, 54),
  Color4F::CreateBy4BitFormat(0, 0, 5),
  Color4F::CreateBy4BitFormat(0, 0, 0),
};

static const Color4F SKY_LIGHT_COLOR[GameConstants::PHASE_DATANUM + 1] =
{
  Color4F::CreateBy4BitFormat(200, 255, 255),
  Color4F::CreateBy4BitFormat(128, 24, 24),
  Color4F::CreateBy4BitFormat(8, 0, 32),
  Color4F::CreateBy4BitFormat(0, 0, 2),
  Color4F::CreateBy4BitFormat(0, 0, 0),
};

static const T_FLOAT SKY_DISTANCE = 500.0f;

static const char* SKY_PROPERTY_NAME_FADE = "_Horizon";
static const char* SKY_PROPERTY_NAME_LIGHT = "_EarthLight";

static const T_UINT16 SHOT_EFFECT_DURATION = 10;

Field::Field()
  : shot_effect_duration_(0)
{
  this->sky_material_ = Asset::Material::SKY.Clone();
  for (T_UINT8 i = 0; i < DIRECTION_DATANUM; ++i)
  {
    this->skys_[i] = new Plane3D();
    this->skys_[i]->SetMaterial(*this->sky_material_);
    this->skys_[i]->GetTransform()->SetPosition(SKY_POSITION[i] * SKY_DISTANCE);
    this->skys_[i]->GetTransform()->SetEularY(MathConstants::DegToRad(SKY_ROTATION[i]));
    this->skys_[i]->GetTransform()->SetScale(SKY_DISTANCE * 2.0f);
    this->AddChild(this->skys_[i]);
  }
  this->zenith_ = new Plane3D();
  this->zenith_->SetMaterial(Asset::Material::ZENITH);
  this->zenith_->GetTransform()->SetPosition(TVec3f(0.0f, 1.0f, 0.0f) * SKY_DISTANCE);
  this->zenith_->GetTransform()->SetEularX(MathConstants::DegToRad(-90.0f));
  this->zenith_->GetTransform()->SetScale(SKY_DISTANCE * 2.0f);
  this->AddChild(this->zenith_);

  this->ground_ = new Plane3D();
  this->ground_->GetTransform()->SetScale(SKY_DISTANCE * 2.0f);
  this->ground_->GetTransform()->SetEularX(MathConstants::DegToRad(90.0f));
  this->ground_->SetMaterial(Asset::Material::GROUND);
  this->ground_->UniqueMaterial();
  this->ground_->GetMaterial()->SetMainTexture(Asset::Texture::FIELD_GROUND);
  this->ground_->GetMaterial()->TextureProperty("_Normal") = &Asset::Texture::FIELD_GROUND_NORMAL;
  this->ground_->GetMaterial()->FloatProperty("_Scale") = this->ground_->GetTransform()->GetScaleMax();
  this->AddChild(this->ground_);
}

Field::~Field()
{
  for (T_UINT8 i = 0; i < DIRECTION_DATANUM; ++i)
  {
    delete this->skys_[i];
  }
  delete this->zenith_;
  delete this->ground_;
}

void Field::Update(Player* player)
{
  if (player->OnShot())
  {
    this->shot_effect_duration_ = SHOT_EFFECT_DURATION;
  }

  bool use_ear = player->IsUseEar();
  for (T_UINT8 i = 0; i < DIRECTION_DATANUM; ++i)
  {
    this->skys_[i]->SetVisible(!use_ear);
  }
  this->zenith_->SetVisible(!use_ear);

  this->ground_->GetMaterial()->BoolProperty("_UseEar") = use_ear;

  if (this->shot_effect_duration_ > 0)
  {
    this->shot_effect_duration_--;
    const TVec3f player_world_position = player->GetTransform()->GetWorldPosition();
    const TVec3f player_world_direction = player->GetController()->GetBulletDirection();
    this->light_brightness_ = 5.0f * sinf((T_FLOAT)this->shot_effect_duration_ / SHOT_EFFECT_DURATION * MathConstants::PI_1_2);
    this->light_diffuse_ = Color4F::WHITE;
    this->light_position_ = player_world_position + player_world_direction;
    this->light_direction_ = player_world_direction;

    this->ground_->GetMaterial()->FloatProperty("_LightBrightness") = this->light_brightness_;
    this->ground_->GetMaterial()->ColorProperty("_LightDiffuse") = this->light_diffuse_;
    this->ground_->GetMaterial()->Vec3fProperty("_LightPosition") = this->light_position_;
    this->ground_->GetMaterial()->Vec3fProperty("_LightDirection") = this->light_direction_;
  }
  
  const T_UINT8 now = GameSceneDirector::GetInstance().GetCurrentPhase();
  const T_UINT8 next = now + 1;
  const T_FLOAT t = GameSceneDirector::GetInstance().GetTimeProgress();
  this->field_ambient_color_ = 
    Color4F::Lerp(SKY_BASE_COLOR[now], SKY_BASE_COLOR[next], t);
  this->field_fade_color_ =
    Color4F::Lerp(SKY_FADE_COLOR[now], SKY_FADE_COLOR[next], t);
  this->field_light_color_ =
    Color4F::Lerp(SKY_LIGHT_COLOR[now], SKY_LIGHT_COLOR[next], t);

  this->zenith_->GetMaterial()->SetDiffuse(this->field_ambient_color_);
  this->sky_material_->SetDiffuse(this->field_ambient_color_);
  this->sky_material_->ColorProperty(SKY_PROPERTY_NAME_FADE) = this->field_fade_color_;
  this->sky_material_->ColorProperty(SKY_PROPERTY_NAME_LIGHT) = this->field_light_color_;
 
  this->ground_->GetMaterial()->ColorProperty("_Ambient") = this->field_light_color_;
}

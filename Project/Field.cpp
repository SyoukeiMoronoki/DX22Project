#include "Field.h"
#include "Asset.h"

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

static const T_FLOAT SKY_DISTANCE = 500.0f;

static const char* SKY_PROPERTY_NAME_FADE = "_Horizon";
static const char* SKY_PROPERTY_NAME_LIGHT = "_EarthLight";

static const Color4F SKY_BASE_COLOR = Color4F::CreateBy4BitFormat(64, 24, 29);
static const Color4F SKY_FADE_COLOR = Color4F::CreateBy4BitFormat(64, 28, 0);
static const Color4F SKY_LIGHT_COLOR = Color4F::CreateBy4BitFormat(64, 24, 24);

static const Color4F DARK_SKY_BASE_COLOR = Color4F::CreateBy4BitFormat(0, 0, 0);
static const Color4F DARK_SKY_FADE_COLOR = Color4F::CreateBy4BitFormat(100, 28, 0);
static const Color4F DARK_SKY_LIGHT_COLOR = Color4F::CreateBy4BitFormat(128, 128, 128);

Field::Field()
{
  this->sky_material_ = Asset::Material::SKY.Clone();
  this->sky_material_->SetDiffuse(SKY_BASE_COLOR);
  this->sky_material_->ColorProperty(SKY_PROPERTY_NAME_FADE) = SKY_FADE_COLOR;
  this->sky_material_->ColorProperty(SKY_PROPERTY_NAME_LIGHT) = SKY_LIGHT_COLOR;
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
  this->zenith_->GetMaterial()->SetDiffuse(SKY_BASE_COLOR);
  this->zenith_->GetTransform()->SetPosition(TVec3f(0.0f, 1.0f, 0.0f) * SKY_DISTANCE);
  this->zenith_->GetTransform()->SetEularX(MathConstants::DegToRad(-90.0f));
  this->zenith_->GetTransform()->SetScale(SKY_DISTANCE * 2.0f);
  this->AddChild(this->zenith_);

  this->ground_ = new Plane3D();
  this->ground_->UniqueMaterial();
  this->ground_->GetMaterial()->SetMainTexture(&Asset::Texture::FIELD_BG);
  this->ground_->GetTransform()->SetEularX(MathConstants::DegToRad(90.0f));
  this->ground_->GetTransform()->SetScale(SKY_DISTANCE * 2.0f);
  //this->AddChild(this->ground_);
}

Field::~Field()
{
  for (T_UINT8 i = 0; i < DIRECTION_DATANUM; ++i)
  {
    delete this->skys_[i];
  }
  delete this->zenith_;
}

void Field::Update()
{
  //this->sky_material_->SetDiffuse(Color4F::Lerp(this->sky_material_->GetDiffuse(), DARK_SKY_BASE_COLOR, 0.015f));
  //this->zenith_->GetMaterial()->SetDiffuse(Color4F::Lerp(this->zenith_->GetMaterial()->GetDiffuse(), DARK_SKY_BASE_COLOR, 0.015f));

  //ShaderProperty_color& fade_color_property = this->sky_material_->ColorProperty(SKY_PROPERTY_NAME_FADE);
  //fade_color_property = Color4F::Lerp(fade_color_property, DARK_SKY_FADE_COLOR, 0.015f);
  //ShaderProperty_color& light_color_property = this->sky_material_->ColorProperty(SKY_PROPERTY_NAME_LIGHT);
  //light_color_property = Color4F::Lerp(light_color_property, DARK_SKY_LIGHT_COLOR, 0.015f);
}

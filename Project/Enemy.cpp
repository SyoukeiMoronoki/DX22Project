#include "Enemy.h"
#include <algorithm>

#include "Asset.h"

#include "IEnemyAttribute.h"
#include "GameSceneDirector.h"
#include "GameSceneDirector.h"
#include "Player.h"

static const T_UINT8 ANIMATION_LENGTH = 4;
static const T_UINT8 ANIMATION_DURATION = 6;
static const T_UINT8 DAMAGE_EFFECT_COUNT = 10;
static const T_UINT8 DAMAGE_MOVE_DELAY = 30;
static const T_UINT8 DEATH_COUNT = 80;

static const T_UINT8 BULLET_EMMISION_DELAY = 120;

Enemy::Enemy()
  : data_(nullptr)
{
  this->body_texture_region_ = new TiledTextureRegion();
  this->body_ = new AnimatedSprite3D();
  this->body_->GetMaterial()->SetBillboardingFlag(true);
  this->body_->SetMaterial(Asset::Material::ENEMY_BODY);
  this->body_->UniqueMaterial();
  this->body_->GetMaterial()->SetZTestLevel(2);
  this->body_->SetTextureRegion(this->body_texture_region_);
  this->AddChild(this->body_);

  this->shadow_texture_region_ = new TiledTextureRegion();
  this->shadow_ = new AnimatedSprite3D();
  this->shadow_->GetMaterial()->SetBillboardingFlag(true);
  this->shadow_->UniqueMaterial();
  this->shadow_->GetMaterial()->SetZTestLevel(1);
  this->shadow_->SetTextureRegion(this->shadow_texture_region_);
  //this->AddChild(this->shadow_);

  this->weak_point_sprite_ = Sprite3D::CreateWithTexture(&Asset::Texture::ENEMY_WEAK_POINT);
  this->weak_point_sprite_->GetMaterial()->SetZTestLevel(1);
  this->weak_point_sprite_->GetMaterial()->SetDiffuse(Color4F::RED);
  this->weak_point_sprite_->SetVisible(false);
  this->body_->AddChild(this->weak_point_sprite_);

  this->weak_point_ = new Collider3D_Sphare(this->weak_point_sprite_);
  this->SetVisible(false);
  this->SetHitRadius(0.5f);
}

Enemy::~Enemy()
{
  delete this->body_texture_region_;
  delete this->body_;
  delete this->shadow_texture_region_;
  delete this->shadow_;
}

void Enemy::OnAllocated()
{
  GameEntity::OnAllocated();
  this->SetEnabled(true);
  this->is_dead_ = false;
  this->count_ = 0;
  this->move_delay_ = 0;
  this->damage_effect_count_ = 0;
  this->death_count_ = 0;
  this->bullet_emmision_delay_ = 0;
  this->GetTransform()->Init();

  this->hit_count_ = 0;
  
  this->body_->Init();
  this->body_->GetTransform()->Init();
  this->body_->Animate(ANIMATION_DURATION);
  this->body_->SetAnimateRange(0, 3);
  this->body_->GetMaterial()->SetDiffuse(Color4F::WHITE);

  this->shadow_->Init();
  this->shadow_->Animate(ANIMATION_DURATION);
  this->shadow_->SetAnimateRange(0, 3);
  this->shadow_->GetMaterial()->SetDiffuse(Color4F::WHITE);

  const Field* field = GameSceneDirector::GetInstance().GetField();
  this->body_->GetMaterial()->MatrixProperty("_World") = this->GetTransform()->GetWorldMatrix();
  this->body_->GetMaterial()->ColorProperty("_Ambient") = field->GetFieldAmbientColor();
  this->body_->GetMaterial()->FloatProperty("_LightBrightness") = field->GetLightBrightness();
  this->body_->GetMaterial()->ColorProperty("_LightDiffuse") = field->GetLightDiffuse();
  this->body_->GetMaterial()->Vec3fProperty("_LightPosition") = field->GetLightPosition();

  //this->shadow_->GetMaterial()->MatrixProperty("_World") = this->GetTransform()->GetWorldMatrix();
  //this->shadow_->GetMaterial()->ColorProperty("_Ambient") = field->GetFieldAmbientColor();
  //this->shadow_->GetMaterial()->FloatProperty("_LightBrightness") = field->GetLightBrightness();
  //this->shadow_->GetMaterial()->ColorProperty("_LightDiffuse") = field->GetLightDiffuse();
  //this->shadow_->GetMaterial()->Vec3fProperty("_LightPosition") = field->GetLightPosition();
}

void Enemy::OnFree()
{
  GameEntity::OnFree();
  this->SetEnabled(false);
  this->SetVisible(false);
}

void Enemy::EnemyUpdate(Player* player)
{
  bool is_sonar = player->IsUseEar();
  this->SetVisible(true);
  this->shadow_->SetVisible(!is_sonar);

  const Field* field = GameSceneDirector::GetInstance().GetField();

  this->body_->GetMaterial()->BoolProperty("_UseEar") = is_sonar;
  this->body_->GetMaterial()->ColorProperty("_Ambient") = field->GetFieldAmbientColor();
  this->body_->GetMaterial()->FloatProperty("_LightBrightness") = field->GetLightBrightness();
  this->body_->GetMaterial()->ColorProperty("_LightDiffuse") = field->GetLightDiffuse();
  this->body_->GetMaterial()->Vec3fProperty("_LightPosition") = field->GetLightPosition();
  this->body_->GetMaterial()->Vec3fProperty("_LightDirection") = field->GetLightDirection();
  this->body_->GetMaterial()->Vec3fProperty("_ViewDirection") = player->GetController()->GetCamera()->GetDirection();

  if (this->death_count_ > 0)
  {
    this->death_count_--;
    this->body_->GetMaterial()->SetDiffuse(Color4F::Lerp(this->body_->GetMaterial()->GetDiffuse(), Color4F(0.0f, 0.0f, 1.0f), 0.25f));
    T_UINT8 death_angle = (T_UINT8)std::min((T_INT32)DEATH_COUNT, ((T_INT32)DEATH_COUNT - (T_INT32)this->death_count_) * 4);
    //this->body_rot_->GetTransform()->SetEularX((T_FLOAT)death_angle / DEATH_COUNT * MathConstants::PI * 0.5f);
    if (this->death_count_ == 0)
    {
      this->is_dead_ = true;
      return;
    }
    return;
  }
  this->weak_point_sprite_->SetVisible(is_sonar);

  this->count_++;

  if (this->move_delay_ > 0)
  {
    this->move_delay_--;
    if (this->move_delay_ == 0)
    {
      this->body_->Animate(ANIMATION_DURATION);
    }
  }
  else
  {
    T_FLOAT width = this->weak_point_sprite_->GetTransform()->GetScaleMax();
    TVec3f target_pos = player->GetTransform()->GetWorldPosition();
    target_pos.y = 0.0f;
    target_pos.x += cosf(this->homing_rad_) * this->homing_radius_;
    target_pos.z += sinf(this->homing_rad_) * this->homing_radius_;
    TVec3f vec = target_pos - this->GetTransform()->GetWorldPosition();
    T_FLOAT length = vec.Length();
    if (length > 0.1f)
    {
      this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + vec / length * this->data_->speed);
      this->bullet_emmision_delay_ = BULLET_EMMISION_DELAY;
    }
    else
    {
      this->bullet_emmision_delay_--;
      if (this->bullet_emmision_delay_ == 0)
      {
        this->bullet_manager_->Emmision(this, player);
        this->bullet_emmision_delay_ = BULLET_EMMISION_DELAY;
      }
    }
  }

  if (this->damage_effect_count_ > 0)
  {
    this->damage_effect_count_--;
  }
  else
  {
    //this->sprite_->SetColor(255, 255, 255);
  }
  if (!this->IsVisible())
  {
    this->SetVisible(true);
  }
}

void Enemy::OnDamaged()
{
  if (this->death_count_ > 0)
  {
    return;
  }
  this->hit_count_++;
  this->damage_effect_count_ = DAMAGE_EFFECT_COUNT;
  this->body_->GetMaterial()->SetDiffuse(255, 128, 128);
  this->SetMoveDelayNegative(DAMAGE_MOVE_DELAY);
  this->body_->Animate(0);
  GameSceneDirector::GetInstance().AddScore(10);
}

void Enemy::OnWeakPointDamaged()
{
  if (this->death_count_ > 0)
  {
    return;
  }
  this->death_count_ = DEATH_COUNT;
  this->SetMoveDelayNegative(DEATH_COUNT);
  this->weak_point_sprite_->SetVisible(false);
  this->body_->Animate(0);
  T_INT8 bonus_rest = std::max(0, this->hit_count_ - 5) + 1;
  GameSceneDirector::GetInstance().AddScore(100 * bonus_rest);
}

void Enemy::AddMoveDelay(T_UINT8 delay)
{
  this->move_delay_ += delay;
}

void Enemy::SetMoveDelayNegative(T_UINT8 delay)
{
  this->move_delay_ = std::max(this->move_delay_, delay);
}

void Enemy::MoveRadialRate(T_FLOAT rate)
{
  //GameEntity::MoveRadialRate(rate);
}

void Enemy::MoveTangential(T_FLOAT value)
{
  if (this->move_delay_ > 0)
  {
    return;
  }
  //GameEntity::MoveTangential(value);
}

void Enemy::SetWeakPoint(const TVec3f& pos)
{
  this->weak_point_sprite_->GetTransform()->SetPosition(pos);
}

bool Enemy::WeakPointHitCheck(Collider3D* collider)
{
  return collider->Collision(*this->weak_point_);
}

void Enemy::Spawn(const EnemyData* data)
{
  this->data_ = data;

  //this->body_->GetTransform()->SetScale(Util::GetRandom(1.0f, 5.0f));
  this->move_delay_ = 30;

  this->body_texture_region_->SetTexture(&data->texture);
  this->body_texture_region_->SetXNum(4);
  this->body_texture_region_->SetYNum(2);
  this->body_texture_region_->FitToTexture();

  this->shadow_texture_region_->SetTexture(&data->texture);
  this->shadow_texture_region_->SetXNum(4);
  this->shadow_texture_region_->SetYNum(2);
  this->shadow_texture_region_->FitToTexture();

  this->body_->FitToTexture();
  this->body_->SetCurrentIndex(0);
  T_FLOAT height = this->body_->GetHeight();
  this->body_->GetMaterial()->SetMainTexture(&data->texture);
  this->body_->GetTransform()->SetY(height * 0.5f);

  this->shadow_->FitToTexture();
  this->shadow_->SetCurrentIndex(0);
  this->shadow_->GetTransform()->SetZ(height * 0.5f);
  this->shadow_->GetMaterial()->SetMainTexture(&data->texture);

  T_FLOAT radius = this->GetRadius() * 0.5f;
  this->weak_point_sprite_->GetTransform()->SetX(Util::GetRandom(-radius, radius));
  this->weak_point_sprite_->GetTransform()->SetY(radius + Util::GetRandom(-radius, radius));
  this->weak_point_sprite_->GetTransform()->SetZ(0.1f);

  //this->data_->attribute->OnAttached(this);
}
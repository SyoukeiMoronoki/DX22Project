#include "Enemy.h"
#include <algorithm>

#include "Asset.h"

#include "IEnemyAttribute.h"
#include "GameSceneDirector.h"
#include "GameSceneDirector.h"

static const T_UINT8 ANIMATION_LENGTH = 4;
static const T_UINT8 ANIMATION_DURATION = 6;
static const T_UINT8 DAMAGE_EFFECT_COUNT = 10;
static const T_UINT8 DAMAGE_MOVE_DELAY = 30;
static const T_UINT8 DEATH_COUNT = 80;

Enemy::Enemy()
  : data_(nullptr)
{
  this->SetBillboardingFlag(true);
  this->texture_region_ = new TiledTextureRegion();
  this->sprite_ = new AnimatedSprite3D();
  this->sprite_->SetBlendFunction(BlendFunction::BLEND_DEFAULT_SRC, BlendFunction::BLEND_DEFAULT_DST);
  this->sprite_->SetLightingEnabled(false);
  this->sprite_->SetZTestFlag(true);
  this->sprite_->SetTextureRegion(this->texture_region_);
  this->AddChild(this->sprite_);

  this->weak_point_sprite_ = new BillBoard();
  this->weak_point_sprite_->SetTexture(Asset::Texture::ENEMY_WEAK_POINT);
  this->weak_point_sprite_->SetLightingEnabled(false);
  //this->weak_point_sprite_->SetColor(Color::RED);
  this->weak_point_sprite_->SetVisible(false);
  this->AddChild(this->weak_point_sprite_);

  this->weak_point_ = new Collider3D_Sphare(this->weak_point_sprite_);
  this->SetVisible(false);
  this->SetHitRadius(0.5f);
}

Enemy::~Enemy()
{
  if (this->texture_region_)
  {
    delete this->texture_region_;
  }
  if (this->sprite_)
  {
    delete this->sprite_;
  }
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
  this->weak_point_ = NULL;
  this->GetTransform()->Init();
  this->sprite_->GetTransform()->Init();
  this->sprite_->GetMaterial()->SetDiffuse(255, 255, 255, 255);
  this->sprite_->Animate(ANIMATION_DURATION);
  this->SetVisible(true);
}

void Enemy::OnFree()
{
  GameEntity::OnFree();
  this->SetEnabled(false);
  this->SetVisible(false);
}

void Enemy::EnemyUpdate(bool is_sonar)
{
  if (is_sonar)
  {
    this->sprite_->SetAnimateRange(ANIMATION_LENGTH, ANIMATION_LENGTH * 2 - 1);
  }
  else
  {
    this->sprite_->SetAnimateRange(0, ANIMATION_LENGTH - 1);
  }
  if (this->death_count_ > 0)
  {
    this->death_count_--;
    T_UINT8 death_angle = (T_UINT8)std::min((T_INT32)DEATH_COUNT, ((T_INT32)DEATH_COUNT - (T_INT32)this->death_count_) * 4);
    this->sprite_->GetTransform()->GetRotator()->SetEularZ((T_FLOAT)death_angle / DEATH_COUNT * MathConstants::PI * 0.5f);
    if (this->death_count_ == 0)
    {
      this->is_dead_ = true;
      return;
    }
    return;
  }
  //this->weak_point_sprite_->SetVisible(facade.IsSonar());
  this->count_++;
  T_FLOAT width = this->weak_point_sprite_->GetTransform()->GetScaleMax();
  //this->weak_point_->SetRadius(std::max(0.0f, 1.0f - this->GetRadialRate() * 1.2f) * 16);
  //this->weak_point_sprite_->GetTransform()->SetScale(this->weak_point_->GetRadius() * 2 / width);
  //if (this->move_delay_ > 0)
  //{
  //  this->move_delay_--;
  //  if (this->move_delay_ == 0)
  //  {
  //    this->sprite_->Animate(ANIMATION_DURATION);
  //  }
  //}
  //else
  //{
  //  //this->data_->attribute->OnUpdate(this);
  //}
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
  //this->data_->attribute->OnDamaged(facade, this);
  //this->damage_effect_count_ = DAMAGE_EFFECT_COUNT;
  //this->sprite_->SetColor(255, 128, 128);
  //this->SetMoveDelayNegative(DAMAGE_MOVE_DELAY);
  //this->sprite_->Animate(0);
  GameSceneDirector::GetInstance().AddScore(10);
}

void Enemy::OnWeakPointDamaged()
{
  if (this->death_count_ > 0)
  {
    return;
  }
  this->sprite_->GetMaterial()->SetDiffuse(32, 32, 100, 255);
  this->death_count_ = DEATH_COUNT;
  this->SetMoveDelayNegative(DEATH_COUNT);
  this->weak_point_sprite_->SetVisible(false);
  this->sprite_->Animate(0);
  GameSceneDirector::GetInstance().AddScore(100);
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
  this->texture_region_->SetTexture(&data->texture);
  this->texture_region_->SetXNum(4);
  this->texture_region_->SetYNum(2);
  this->texture_region_->FitToTexture();
  this->sprite_->FitToTexture();
  this->sprite_->SetCurrentIndex(0);
  //this->data_->attribute->OnAttached(this);
}
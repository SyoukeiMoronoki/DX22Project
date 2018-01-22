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
  this->texture_region_ = new TiledTextureRegion();
  this->body_ = new Cube3D();
  this->body_->SetMaterial(Asset::Material::ENEMY_BODY);
  this->AddChild(this->body_);

  this->weak_point_sprite_ = Sprite3D::CreateWithTexture(&Asset::Texture::ENEMY_WEAK_POINT);
  this->weak_point_sprite_->GetMaterial()->SetZTestLevel(2);
  this->weak_point_sprite_->GetMaterial()->SetDiffuse(Color4F::RED);
  this->weak_point_sprite_->SetVisible(false);
  this->weak_point_sprite_->SetBillboardingFlag(true);
  this->AddChild(this->weak_point_sprite_);

  this->weak_point_ = new Collider3D_Sphare(this->weak_point_sprite_);
  this->SetVisible(false);
  this->SetHitRadius(0.5f);
}

Enemy::~Enemy()
{
  delete this->texture_region_;
  delete this->body_;
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
  this->body_->Init();
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
  if (this->death_count_ > 0)
  {
    this->death_count_--;
    //T_UINT8 death_angle = (T_UINT8)std::min((T_INT32)DEATH_COUNT, ((T_INT32)DEATH_COUNT - (T_INT32)this->death_count_) * 4);
    //this->sprite_->GetTransform()->SetEularZ((T_FLOAT)death_angle / DEATH_COUNT * MathConstants::PI * 0.5f);
    if (this->death_count_ == 0)
    {
      this->is_dead_ = true;
      return;
    }
    return;
  }
  this->weak_point_sprite_->SetVisible(is_sonar);
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
  this->death_count_ = DEATH_COUNT;
  this->SetMoveDelayNegative(DEATH_COUNT);
  this->weak_point_sprite_->SetVisible(false);
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
  
  this->body_->GetTransform()->SetScale(Util::GetRandom(1.0f, 5.0f));
  T_FLOAT radius = this->GetRadius();

  this->body_->GetTransform()->SetY(radius);
  this->weak_point_sprite_->GetTransform()->SetX(Util::GetRandom(-radius, radius));
  this->weak_point_sprite_->GetTransform()->SetY(radius + Util::GetRandom(-radius, radius));
  this->weak_point_sprite_->GetTransform()->SetZ(Util::GetRandom(-radius, radius));

  this->texture_region_->SetTexture(&data->texture);
  this->texture_region_->SetXNum(4);
  this->texture_region_->SetYNum(2);
  this->texture_region_->FitToTexture();
  //this->data_->attribute->OnAttached(this);
}
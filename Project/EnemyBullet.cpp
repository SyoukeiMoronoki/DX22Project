#include "EnemyBullet.h"

#include "Asset.h"

EnemyBullet::EnemyBullet()
{
  this->body_ = Sprite3D::CreateWithTexture(&Asset::Texture::PLAYER_BULLET);
  this->body_->GetMaterial()->SetZTestLevel(2);
  this->body_->SetBillboardingFlag(true);
  this->AddChild(this->body_);
  this->SetHitRadius(1.0f);
}

void EnemyBullet::OnAllocated()
{
  GameEntity::OnAllocated();
  this->velocity_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->lifetime_ = 100;
}

void EnemyBullet::OnFree()
{
  GameEntity::OnFree();
}

void EnemyBullet::Update()
{
  if (!this->IsAlive())
  {
    return;
  }
  this->lifetime_--;
  this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + this->velocity_);

}

void EnemyBullet::OnHited()
{
  this->lifetime_ = 0;
}

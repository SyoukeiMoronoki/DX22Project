#include "Bullet.h"

#include "Asset.h"

Bullet::Bullet()
{
  this->body_ = Sprite3D::CreateWithTexture(&Asset::Texture::PLAYER_BULLET);
  this->body_->GetMaterial()->SetZTestLevel(1);
  this->body_->SetBillboardingFlag(true);
  this->AddChild(this->body_);
  this->SetHitRadius(1.0f);
}

void Bullet::OnAllocated()
{
  GameEntity::OnAllocated();
  this->velocity_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->lifetime_ = 100;
}

void Bullet::OnFree()
{
  GameEntity::OnFree();
}

void Bullet::Update()
{
  if (!this->IsAlive())
  {
    return;
  }
  this->lifetime_--;
  this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + this->velocity_);
}

void Bullet::OnHitEnemy()
{
  this->lifetime_ = 0;
}

#include "BossBullet.h"

#include "Asset.h"

BossBullet::BossBullet()
{
  this->body_ = Sprite3D::CreateWithTexture(Asset::Texture::PLAYER_BULLET);
  this->body_->GetMaterial()->SetZTestLevel(2);
  this->body_->GetMaterial()->SetBillboardingFlag(true);
  this->body_->GetTransform()->SetScale(2.0f);
  this->AddChild(this->body_);
  this->SetHitRadius(1.0f);
}

BossBullet::~BossBullet()
{
  delete this->body_;
}

void BossBullet::OnAllocated()
{
  GameEntity::OnAllocated();
  this->velocity_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->lifetime_ = 100;
}

void BossBullet::OnFree()
{
  GameEntity::OnFree();
}

void BossBullet::Update()
{
  if (!this->IsAlive())
  {
    return;
  }
  this->lifetime_--;
  this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + this->velocity_);

}

void BossBullet::OnHited()
{
  this->lifetime_ = 0;
}

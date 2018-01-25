#include "PlayerActor.h"

PlayerActor::PlayerActor(GameObject3D* player)
  : player_(player)
{
  //this->GetTransform()->SetEularY(MathConstants::PI_1_2);
  this->body_ = new Cube3D();
  this->body_->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);
  this->body_->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
  this->body_->UniqueMaterial();
  //this->body_->SetLightingEnabled(false);
  this->body_->SetLayerId(1);
  this->AddChild(this->body_);

  this->gun_ = new Cube3D();
  this->gun_->GetTransform()->SetScale(0.1f, 0.1f, 1.0f);
  this->gun_->GetTransform()->SetPosition(0.0f, 0.0f, 0.5f);
  this->gun_->UniqueMaterial();
  //this->gun_->SetLightingEnabled(false);
  this->gun_->SetLayerId(1);
  this->AddChild(this->gun_);
}

PlayerActor::~PlayerActor()
{
  delete this->body_;
  delete this->gun_;
}

void PlayerActor::Update()
{
  this->GetTransform()->LerpRotation(this->direction_quaternion_, 0.25f);
}

void PlayerActor::Walk(T_FLOAT x, T_FLOAT y)
{
  T_FLOAT rad = -atan2f(y, x) + MathConstants::PI_1_2;
  this->direction_quaternion_ = Quaternion(TVec3f(0.0f, 1.0f, 0.0f), rad);
}

void PlayerActor::Face(const Quaternion& direction_quaternion)
{
  this->direction_quaternion_ = direction_quaternion;
}

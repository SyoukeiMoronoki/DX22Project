#include "BossBody.h"
#include "Asset.h"

static const T_FLOAT SPEED = 0.3f;

BossBody::BossBody()
{
  Cube3D* cube = new Cube3D();
  this->AddChild(cube);
  this->body_ = Sprite3D::CreateWithTexture(&Asset::Texture::ENEMY_WEAK_POINT);
  this->body_->GetMaterial()->SetZTestLevel(1);
  this->SetBillboardingFlag(true);
  this->AddChild(this->body_);
  //this->SetVisible(false);
}

BossBody::~BossBody()
{
  delete this->body_;
}

void BossBody::OnAllocated()
{
  this->SetVisible(true);
}

void BossBody::OnFree()
{
  this->SetVisible(false);
}

void BossBody::BodyUpdate(BossBody* front)
{
  if (!front)
  {
    this->GetTransform()->RotateY(0.1f);
    this->GetTransform()->MoveZ(0.5f);
    return;
  }
  TVec3f distance = front->GetTransform()->GetWorldPosition() - this->GetTransform()->GetWorldPosition();
  T_FLOAT distance_length = distance.Length();
  if (distance_length < 0.01f)
  {
    return;
  }
  T_FLOAT speed = std::min(distance_length, SPEED);
  this->GetTransform()->LerpRotation(front->GetTransform()->GetQuaternion(), 0.5f);
  this->GetTransform()->MoveZ(speed);
}

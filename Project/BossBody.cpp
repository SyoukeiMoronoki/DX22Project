#include "BossBody.h"
#include "Asset.h"

static const T_FLOAT SPEED = 0.3f;

BossBody::BossBody()
{
  Cube3D* cube = new Cube3D();
  this->AddChild(cube);
  this->body_ = Sprite3D::CreateWithTexture(&Asset::Texture::ENEMY_WEAK_POINT);
  this->body_->GetMaterial()->SetZTestLevel(1);
  //this->body_->SetBillboardingFlag(true);
  this->AddChild(this->body_);
  //this->SetVisible(false);
  this->rot_velocity_ = TVec3f(0.01f, 0.05f, 0.001f);
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

void BossBody::BodyUpdate(BossBody* front, Player* player)
{
  this->BodyMoveProcess(front);
  const TVec3f player_pos = player->GetTransform()->GetWorldPosition();
  const TVec3f pos = this->GetTransform()->GetWorldPosition();
  
  const T_FLOAT offsetY = this->GetTransform()->GetScaleY() * 0.5f;
  if (pos.y < offsetY)
  {
    this->GetTransform()->SetY(offsetY);
  }
}

void BossBody::BodyMoveProcess(BossBody* front)
{
  if (!front)
  {
    //this->GetTransform()->RotateZ(this->rot_velocity_.z);
    this->GetTransform()->RotateY(this->rot_velocity_.y);
    this->GetTransform()->RotateX(this->rot_velocity_.x);
    this->GetTransform()->MoveZ(SPEED);
    TVec3f pos = this->GetTransform()->GetWorldPosition();
    if (pos.y < 0.0f || pos.y > 10.0f)
    {
      this->rot_velocity_.x *= -1.0f;
    }
    return;
  }
  TVec3f distance = front->GetTransform()->GetWorldPosition() - this->GetTransform()->GetWorldPosition();
  T_FLOAT distance_length = distance.Length();
  if (distance_length < this->GetTransform()->GetScaleMax())
  {
    return;
  }
  T_FLOAT speed = std::min(distance_length, SPEED);
  this->GetTransform()->LerpRotation(front->GetTransform()->GetQuaternion(), 0.1f);
  this->GetTransform()->MoveZ(speed);
}

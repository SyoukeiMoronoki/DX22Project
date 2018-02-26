#include "BossBody.h"
#include "Asset.h"
#include "GameDirector.h"
#include "GameSceneDirector.h"
#include "Field.h"
#include "BossController.h"
#include "BossBrain.h"


BossBody::BossBody()
{
  Material* mat = Asset::Material::ENEMY_BODY.Clone();
  mat->SetMainTexture(Asset::Texture::ENEMY_BOSS);
  this->body_ = AnimatedSprite3D::CreateWithMaterial(*mat, 2, 2);
  this->body_->GetMaterial()->SetZTestLevel(1);
  this->body_->GetMaterial()->SetBillboardingFlag(true);

  this->body_->GetMaterial()->MatrixProperty("_World") = &this->GetTransform()->GetWorldMatrix();
  this->body_->SetVisible(false);

  this->weak_point_sprite_ = Sprite3D::CreateWithTexture(Asset::Texture::ENEMY_WEAK_POINT);
  this->weak_point_sprite_->GetMaterial()->SetZTestLevel(1);
  this->weak_point_sprite_->GetMaterial()->SetDiffuse(Color4F::RED);
  this->weak_point_sprite_->SetVisible(false);
  this->weak_point_sprite_->GetTransform()->SetScale(4.0f);
  this->body_->AddChild(this->weak_point_sprite_);

  GameDirector::GetScene()->AddChild(this->body_);
  this->GetTransform()->SetScale(3.0f);
  this->SetHitRadius(1.0f);
  this->weak_flag_ = false;
}

BossBody::~BossBody()
{
  delete this->body_;
  delete this->weak_point_sprite_;
}

void BossBody::OnAllocated()
{
  this->SetVisible(true);
}

void BossBody::OnFree()
{
  this->SetVisible(false);
}

void BossBody::HeadUpdate(BossController* controller, Player* player)
{
  this->move_direction_ += (this->GetTransform()->GetWorldPosition() - this->old_position_).Normalized();
  this->move_direction_ *= 0.5f;
  this->old_position_ = this->GetTransform()->GetWorldPosition();

  this->body_->SetCurrentIndex(0);

  controller->GetBrain()->Update(controller, this, player);

  this->UpdateProperties(controller, player);
}

void BossBody::BodyUpdate(BossController* controller, BossBody* front, Player* player)
{
  this->move_direction_ += (this->GetTransform()->GetWorldPosition() - this->old_position_).Normalized();
  this->move_direction_ *= 0.5f;
  this->old_position_ = this->GetTransform()->GetWorldPosition();

  this->body_->SetCurrentIndex(1);

  TVec3f target = front->GetTransform()->GetWorldPosition() - front->GetMoveDirection() * this->GetTransform()->GetScaleMax();
  TVec3f distance = target - this->GetTransform()->GetWorldPosition();
  T_FLOAT speed = std::min(controller->GetSpeed(), distance.Length());
  this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + distance.Normalized() * speed);

  this->UpdateProperties(controller, player);

  T_INT32 rand = Util::GetRandom(0, 1000);
  if (rand <= 2)
  {
    this->weak_flag_ = !this->weak_flag_;
  }
}

void BossBody::OnDamaged()
{
  GameSceneDirector::GetInstance().AddScore(30);
}

void BossBody::OnWeakPointDamaged()
{
  GameSceneDirector::GetInstance().AddScore(300);
}

void BossBody::UpdateProperties(BossController* controller, Player* player)
{
  const TVec3f player_pos = player->GetTransform()->GetWorldPosition();
  const TVec3f pos = this->GetTransform()->GetWorldPosition();

  const T_FLOAT offsetY = this->GetTransform()->GetScaleY();
  if (pos.y < offsetY)
  {
    this->GetTransform()->SetY(offsetY);
  }

  this->body_->GetTransform()->SetPosition(this->GetTransform()->GetPosition());
  this->body_->GetTransform()->SetScale(this->GetTransform()->GetScaleMax());
  this->body_->SetVisible(this->IsVisible());

  bool is_sonar = player->IsUseEar();
  const Field* field = GameSceneDirector::GetInstance().GetField();

  this->weak_point_sprite_->SetVisible(is_sonar && this->weak_flag_);
  this->body_->GetMaterial()->BoolProperty("_UseEar") = is_sonar;
  this->body_->GetMaterial()->ColorProperty("_Ambient") = field->GetFieldAmbientColor();
  this->body_->GetMaterial()->FloatProperty("_LightBrightness") = field->GetLightBrightness();
  this->body_->GetMaterial()->ColorProperty("_LightDiffuse") = field->GetLightDiffuse();
  this->body_->GetMaterial()->Vec3fProperty("_LightPosition") = field->GetLightPosition();
  this->body_->GetMaterial()->Vec3fProperty("_LightDirection") = field->GetLightDirection();
  this->body_->GetMaterial()->Vec3fProperty("_ViewDirection") = player->GetController()->GetCamera()->GetDirection();
}

void BossBody::Move(TVec3f value)
{
  //T_FLOAT dot = TVec3f::InnerProduct(this->GetMoveDirection(), value);
  //if (dot < -0.5f)
  //{
  //  value = TVec3f::OuterProduct(value, this->GetMoveDirection());
  //}
  this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + value);
}

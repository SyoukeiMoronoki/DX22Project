#include "PlayerController_Walk.h"
#include "GameInput.h"
#include "Player.h"
#include "GameSceneDirector.h"

PlayerController_Walk::PlayerController_Walk(Player* player)
  : PlayerController(player)
{
  this->camera_->GetRenderState()->AddTargetLayerId(1);
}

void PlayerController_Walk::OnStart(const PlayerController* prev)
{
  this->player_->GetActor()->GetTransform()->SetEularY(0.0f);
  this->camera_->GetTransform()->SetEularAngles(TVec3f(0.0f, 0.0f, 0.0f));
  this->direction_quaternion_.FromRotationMatrix(*this->player_->GetActor()->GetTransform()->GetWorldMatrix());
  this->next_camera_pos_ = TVec3f(0.0f, 2.5f, -9.0f);
  this->next_look_at_pos_ = TVec3f(0.0f, 0.0f, 0.5f);
  this->camera_quaternion_ = Quaternion();
  this->camera_distance_ = this->next_camera_pos_.Length();
}

void PlayerController_Walk::OnEnd()
{
}

void PlayerController_Walk::ControllProcess()
{
  using namespace HalEngine;
  using namespace GameInput;
  
  this->camera_->GetTransform()->SetPosition(TVec3f::EaseIn(
    EasingFunction::Quadratic::GetInstance(),
    this->camera_->GetTransform()->GetPosition(),
    this->next_camera_pos_,
    0.25f
  ));
  this->camera_->SetLookAtPos(TVec3f::EaseIn(
    EasingFunction::Quadratic::GetInstance(),
    this->camera_->GetLookAtPos(),
    this->next_look_at_pos_,
    0.25f
  ));
  this->camera_->GetTransform()->LerpRotation(
    this->camera_quaternion_,
    0.25f
  );

  this->player_->GetTransform()->LerpRotation(
    this->direction_quaternion_,
    0.25f
  );

  this->camera_->Update();

  const T_FLOAT dx = Input(0)->GetAxis(X_AXIS);
  const T_FLOAT dy = Input(0)->GetAxis(Y_AXIS);
  this->player_->GetTransform()->MoveX(dx * 0.15f);
  this->player_->GetTransform()->MoveZ(dy * 0.15f);
  if (dx != 0.0f || dy != 0.0f)
  {
    this->player_->GetActor()->Walk(dx, dy);
  }
  if (Input(0)->GetButtonDown(FOCUS))
  {
    BossBody* target = GameSceneDirector::GetInstance().GetBoss()->GetHead();
    //this->camera_->SetTarget(target);
    //this->camera_->SetLookAtPos(target->GetTransform()->GetWorldPosition());
    TVec3f player_direction = this->player_->GetTransform()->GetDirection();
    ////player_pos.y = 0.0f;
    //TVec3f target_direction = target->GetTransform()->GetWorldPosition() - this->player_->GetTransform()->GetWorldPosition();
    //this->direction_quaternion_ = this->direction_quaternion_.LookRotation(
    //  target_direction
    //);
    TVec3f target_pos = target->GetTransform()->GetWorldPosition();
    TVec3f player_pos = this->player_->GetActor()->GetTransform()->GetWorldPosition();
    TVec3f camera_pos = this->camera_->GetTransform()->GetWorldPosition();

    //this->camera_quaternion_ = 

    TVec3f target_distance = target_pos - player_pos;
    //this->next_camera_pos_ = camera_pos;
    //this->next_camera_pos_.x = 0.0f;
    this->next_look_at_pos_ = target_pos - camera_pos;
    this->next_look_at_pos_.x = 0.0f;
    //this->next_look_at_pos_.y = std::max(this->next_look_at_pos_.y, 20.0f);

    this->direction_quaternion_ = Quaternion(TVec3f(0.0f, 1.0f, 0.0f), -atan2f(target_distance.z, target_distance.x) + MathConstants::PI_1_2);
    this->player_->GetActor()->Face(Quaternion());

    //this->direction_quaternion_.FromRotationMatrix(*this->player_->GetActor()->GetTransform()->GetWorldMatrix());
    //this->player_->GetActor()->Face();
  }
}

void PlayerController_Walk::OnAttack()
{
}

const TVec3f PlayerController_Walk::GetBulletDirection() const
{
  TVec3f pos = TVec3f();
  TVec3f direction = this->player_->GetActor()->GetTransform()->GetDirection();
  this->camera_->GetTransform()->GetWorldMatrix()->Apply(&pos);
  this->camera_->GetTransform()->GetWorldMatrix()->Apply(&direction);
  return (direction - pos).Normalized();
}

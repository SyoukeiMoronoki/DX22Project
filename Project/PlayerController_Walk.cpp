#include "PlayerController_Walk.h"
#include "GameInput.h"
#include "Player.h"

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
    TVec3f(0.0f, 1.0f, -4.0f),
    0.25f
  ));
  this->camera_->SetLookAtPos(TVec3f::EaseIn(
    EasingFunction::Quadratic::GetInstance(),
    this->camera_->GetLookAtPos(),
    TVec3f(0.0f, 0.0f, 1.0f),
    0.25f
  ));
  this->player_->GetTransform()->LerpRotation(
    this->direction_quaternion_,
    0.25f
  );

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
    this->direction_quaternion_.FromRotationMatrix(*this->player_->GetActor()->GetTransform()->GetWorldMatrix());
    this->player_->GetActor()->Face();
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

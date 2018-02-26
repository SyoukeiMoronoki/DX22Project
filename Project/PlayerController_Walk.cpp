#include "PlayerController_Walk.h"
#include "GameInput.h"
#include "Player.h"
#include "GameSceneDirector.h"

static const T_UINT8 TARGET_DOUBLE_TAP_DURATION = 30;
static const TVec3f DEFAULT_CAMERA_POS = TVec3f(0.0f, 2.5f, -9.0f);
static const TVec3f DEFAULT_LOOK_AT_POS = TVec3f(0.0f, 0.0f, 0.5f);

PlayerController_Walk::PlayerController_Walk(Player* player)
  : PlayerController(player)
{
  this->camera_->GetRenderState()->AddTargetLayerId(1);
  this->is_target_mode_ = false;
}

void PlayerController_Walk::OnStart(const PlayerController* prev)
{
  this->player_->GetActor()->GetTransform()->SetEularY(0.0f);
  this->camera_->GetTransform()->SetEularAngles(TVec3f(0.0f, 0.0f, 0.0f));
  this->direction_quaternion_.FromRotationMatrix(this->player_->GetActor()->GetTransform()->GetWorldMatrix());
  this->next_camera_pos_ = DEFAULT_CAMERA_POS;
  this->next_look_at_pos_ = DEFAULT_LOOK_AT_POS;
  this->camera_quaternion_ = Quaternion();
  this->camera_distance_ = this->next_camera_pos_.Length();
  this->target_double_tap_duration_ = 0;
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
  if (!this->is_target_mode_)
  {
    this->next_camera_pos_ = DEFAULT_CAMERA_POS;
    this->next_look_at_pos_ = DEFAULT_LOOK_AT_POS;
  }
  bool focus_button_pushing = Input(0)->GetButton(FOCUS);
  if (!focus_button_pushing)
  {
    this->target_double_tap_duration_ = 0;
  }
  BossBody* target = GameSceneDirector::GetInstance().GetBoss()->GetHead();
  if (GameSceneDirector::GetInstance().GetCurrentPhase() == GameConstants::PHASE_DARK)
  {
    target = nullptr;
    this->is_target_mode_ = false;
  }
  if (focus_button_pushing)
  {
    if (target)
    {
      this->target_double_tap_duration_++;
      if (this->target_double_tap_duration_ > TARGET_DOUBLE_TAP_DURATION)
      {
        this->is_target_mode_ = !this->is_target_mode_;
      }
    }
    if (!this->is_target_mode_ || !target)
    {
      this->direction_quaternion_.FromRotationMatrix(this->player_->GetActor()->GetTransform()->GetWorldMatrix());
      this->player_->GetActor()->Face(Quaternion());
    }
  }
  if (this->is_target_mode_ && target)
  {
    TVec3f player_direction = this->player_->GetTransform()->GetDirection();
    TVec3f target_pos = target->GetTransform()->GetWorldPosition();
    TVec3f player_pos = this->player_->GetActor()->GetTransform()->GetWorldPosition();

    TVec3f target_distance = target_pos - player_pos;
    TVec3f camera_pos = target_distance + target_distance.Normalized() * this->camera_distance_;
    this->next_camera_pos_ = -target_distance.Normalized() * this->camera_distance_;
    this->next_camera_pos_.z = -std::max(2.0f, sqrtf(this->next_camera_pos_.x * this->next_camera_pos_.x + this->next_camera_pos_.z * this->next_camera_pos_.z));
    this->next_camera_pos_.x = 0.0f;
    this->next_camera_pos_.y = std::max(0.0f, std::min(5.0f, this->next_camera_pos_.y));

    this->next_look_at_pos_ = target_pos - (player_pos + this->next_camera_pos_);
    this->next_look_at_pos_.z = std::max(2.0f, sqrtf(this->next_look_at_pos_.x * this->next_look_at_pos_.x + this->next_look_at_pos_.z * this->next_look_at_pos_.z));
    this->next_look_at_pos_.x = 0.0f;
    this->next_look_at_pos_.y = std::max(0.0f, std::min(5.0f, this->next_look_at_pos_.y));
    this->direction_quaternion_ = Quaternion(TVec3f(0.0f, 1.0f, 0.0f), -atan2f(camera_pos.z, camera_pos.x) + MathConstants::PI_1_2);
  }
}

void PlayerController_Walk::OnAttack()
{
}

const TVec3f PlayerController_Walk::GetBulletDirection() const
{
  TVec3f pos = TVec3f();
  TVec3f direction = this->player_->GetActor()->GetTransform()->GetDirection();
  this->camera_->GetTransform()->GetWorldMatrix().Apply(&pos);
  this->camera_->GetTransform()->GetWorldMatrix().Apply(&direction);
  return (direction - pos).Normalized();
}

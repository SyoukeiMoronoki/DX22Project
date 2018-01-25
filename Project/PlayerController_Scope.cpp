#include "PlayerController_Scope.h"
#include "GameInput.h"
#include "Player.h"

PlayerController_Scope::PlayerController_Scope(Player* player)
  : PlayerController(player)
  , cursol_(new PlayerUI_Cursol())
  , look_at_pos_(0.0f, 0.0f, 1.0f)
{
  this->UIRoot_->AddChild(this->cursol_);
}

PlayerController_Scope::~PlayerController_Scope()
{
  delete this->cursol_;
}

void PlayerController_Scope::OnStart(const PlayerController* prev)
{
  this->look_quaternion_.FromRotationMatrix(*this->player_->GetActor()->GetTransform()->GetWorldMatrix());
  this->player_->GetActor()->Face(Quaternion());
  this->look_at_pos_ = TVec3f(0.0f, 0.0f, 1.0f);
}

void PlayerController_Scope::OnEnd()
{
}

void PlayerController_Scope::ControllProcess()
{
  using namespace HalEngine;
  using namespace GameInput;
  
  this->camera_->GetTransform()->SetPosition(TVec3f::Lerp(
    this->camera_->GetTransform()->GetPosition(),
    TVec3f(0.0f, 0.0f, 0.0f),
    0.25f
  ));
  this->camera_->SetLookAtPos(TVec3f::Lerp(
    this->camera_->GetLookAtPos(),
    this->look_at_pos_,
    0.25f
  ));
  this->player_->GetTransform()->LerpRotation(
    this->look_quaternion_,
    0.25f
  );

  this->camera_->GetTransform()->SetPosition(this->camera_->GetTransform()->GetPosition() * 0.75f);
  const T_FLOAT dx = Input(0)->GetAxis(X_AXIS) * 0.015f;
  const T_FLOAT dy = Input(0)->GetAxis(Y_AXIS) * 0.015f;
  if (dx != 0.0f)
  {
    this->look_quaternion_.q(TVec3f(0.0f, 1.0f, 0.0f), dx);
  }
  if (dy != 0.0f)
  {
    this->look_at_pos_.y = std::min(std::max(this->look_at_pos_.y + dy, -1.0f), 1.0f);
  }
}

void PlayerController_Scope::OnAttack()
{
  this->cursol_->OnAttack();
  TVec3f pos = this->camera_->GetLookAtPos();
  pos.y += 0.05f;
  this->camera_->GetTransform()->SetPosition(pos * -0.5f);
}

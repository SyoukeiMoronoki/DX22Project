#include "PlayerController.h"
#include "GameDirector.h"
#include "Player.h"

PlayerController::PlayerController(Player* player)
  : player_(player)
  , camera_(new Camera3D_LookAt())
  , UIRoot_(new GameObject2D())
{
  this->camera_->SetPlayer(player);
  this->camera_->SetEnabled(false);
  GameDirector::GetScene()->AddCamera(this->camera_);
  this->UIRoot_->SetVisible(false);
  GameDirector::GetScene()->AddChild(this->UIRoot_);
}

PlayerController::~PlayerController()
{
  delete this->camera_;
  delete this->UIRoot_;
}

void PlayerController::Start(const PlayerController* prev)
{
  if (prev)
  {
    this->camera_->GetTransform()->SetPosition(prev->GetCameraPosition());
    this->camera_->SetLookAtPos(prev->GetCameraLookAtPosition());
  }
  this->OnStart(prev);
  this->camera_->SetEnabled(true);
  this->UIRoot_->SetVisible(true);
}

void PlayerController::End()
{
  this->OnEnd();
  this->camera_->SetEnabled(false);
  this->UIRoot_->SetVisible(false);
}


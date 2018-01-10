#include "PlayerCamera.h"
#include "Player.h"
#include "GameDirector.h"

PlayerCamera::PlayerCamera()
{
  this->camera_ = new Camera3D_LookAt();
  this->camera_->GetRenderState()->AddTargetLayerId(0);
  this->camera_->SetEnabled(true);
  this->camera_->GetTransform()->SetY(3.0f);
  this->camera_->GetTransform()->SetZ(-10.0f);
  GameDirector::GetScene()->AddCamera(this->camera_);
}

PlayerCamera::~PlayerCamera()
{
  delete this->camera_;
}

void PlayerCamera::RegisterToScene(Scene* scene)
{
  scene->AddCamera(this->camera_);
}

void PlayerCamera::RegisterToPlayer(Player* player)
{
  this->camera_->SetPlayer(player);
}

void PlayerCamera::Update()
{
  this->camera_->Update();
}

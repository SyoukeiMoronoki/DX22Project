#include "PlayerCamera.h"
#include "Player.h"

//static void CameraInit(Camera3D* camera, T_UINT8 id, T_UINT8 x_num, T_UINT8 y_num)
//{
//  const T_FLOAT screen_width = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
//  const T_FLOAT screen_height = (T_FLOAT)Director::GetInstance()->GetScreenHeight();
//  if (player_id == 0)
//  {
//    camera->SetViewportX(0);
//    camera->SetViewportY(0);
//    camera->SetViewportWidth(player_count);
//    if (player_count == 1)
//    {
//      camera->SetViewportWidth(screen_width);
//      camera->SetViewportHeight(screen_height);
//      return;
//    }
//    if (player_count == 1)
//    {
//      camera->SetViewportWidth(screen_width);
//      camera->SetViewportHeight(screen_height);
//      return;
//    }
//    if (player_count == 1)
//    {
//      camera->SetViewportWidth(screen_width);
//      camera->SetViewportHeight(screen_height);
//      return;
//    }
//    return;
//  }
//  if (player_id == 1)
//  {
//
//  }
//
//  camera->SetViewportX(x);
//  camera->SetViewportY(y);
//}

PlayerCamera::PlayerCamera(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height)
{
  this->camera_ = new Camera3D_LookAt();
  this->camera_->GetRenderState()->AddTargetLayerId(0);
  //this->camera_->SetPlayer(this);
  this->camera_->SetViewportX(x);
  this->camera_->SetViewportY(y);
  this->camera_->SetViewportWidth(width);
  this->camera_->SetViewportHeight(height);
  this->camera_->SetViewportZMin(0.0f);
  this->camera_->SetViewportZMax(1.0f);
  this->camera_->SetEnabled(true);
  this->camera_->GetTransform()->SetY(3.0f);
  this->camera_->GetTransform()->SetZ(-10.0f);
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

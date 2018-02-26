#include "GameEntity.h"
#include <algorithm>

#include "GameSceneDirector.h"

GameEntity::GameEntity()
  : is_enabled_(false)
{
  this->collider_ = new GameEntityCollider(this);
  this->SetVisible(false);
}

GameEntity::~GameEntity()
{
  delete this->collider_;
}

void GameEntity::OnAllocated()
{
  this->SetVisible(true);
}

void GameEntity::OnFree()
{
  this->SetVisible(false);
}

//void GameEntity::ApplyViewPort(const ViewPort& viewport)
//{
//  this->radial_rate_ = std::min(1.0f, std::max(0.0f, this->radial_rate_));
//  //最短距離での円周のwidth
//  const T_FLOAT near_world_width = viewport.GetNear() * 2 * MathConstants::PI;
//  //このオブジェクトの表示スケール
//  const T_FLOAT scale = viewport.GetNear() / (viewport.GetNear() + viewport.GetDepthRange() * this->radial_rate_);
//
//  //このオブジェクトの距離での円周のwidth
//  const T_FLOAT tangential_world_width = near_world_width / scale;
//
//  T_FLOAT tangential_pos = this->tangential_rate_ * tangential_world_width;
//  tangential_pos += this->tangential_move_;
//  this->tangential_move_ = 0;
//  this->tangential_rate_ = tangential_pos / tangential_world_width;
//  if (this->tangential_rate_ > 1.0f)
//  {
//    this->tangential_rate_ -= 1.0f;
//  }
//  else if (this->tangential_rate_ < 0.0f)
//  {
//    this->tangential_rate_ += 1.0f;
//  }
//  
//  const T_FLOAT width = this->GetViewSize().width / tangential_world_width;
//  const T_FLOAT left = this->tangential_rate_ - width * 0.5f;
//  const T_FLOAT right = this->tangential_rate_ + width * 0.5f;
//
//  const T_FLOAT camera_angle_tangential_rate = viewport.GetCameraAngleRad() / MathConstants::PI2;
//  const T_FLOAT viewing_angle_tangential_rate = viewport.GetViewingAngleRad() / MathConstants::PI2;
//  const T_FLOAT view_left = camera_angle_tangential_rate + viewing_angle_tangential_rate * 0.5f;
//  const T_FLOAT view_right = camera_angle_tangential_rate + viewing_angle_tangential_rate * -0.5f;
//
//  //if (left > view_right || right < view_left)
//  //{
//  //  this->SetVisible(false);
//  //  return;
//  //}
//
//  const T_FLOAT near_screen_width = near_world_width * viewport.GetViewingAngleRad() / MathConstants::PI2;
//  const T_FLOAT view_scale = viewport.GetScreenWidth() / near_screen_width;
//  const T_FLOAT view_tangential_rate = viewport.GetCameraAngleRad() / MathConstants::PI2;
//  const T_FLOAT rate_min = this->tangential_rate_ < view_tangential_rate ? this->tangential_rate_ : view_tangential_rate;
//  const T_FLOAT rate_max = this->tangential_rate_ > view_tangential_rate ? this->tangential_rate_ : view_tangential_rate;
//  const T_FLOAT rate_a = (rate_max - rate_min);
//  const T_FLOAT rate_b = (1.0f + rate_min - rate_max);
//  T_FLOAT pos_x = near_world_width * ((rate_a < rate_b ? rate_a : -rate_b));
//  if (rate_max == view_tangential_rate)
//  {
//    pos_x *= -1;
//  }
//
//  this->SetZIndex((T_INT8)((1.0 - this->radial_rate_) * 20));
//  this->ChangeTransform(view_scale * scale, pos_x * view_scale, -100);
//}

bool GameEntity::HitCheck(Collider3D* collider)
{
  return collider->Collision(*this->collider_);
}

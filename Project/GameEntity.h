#pragma once

#include <HalEngine.h>

#include "GameEntityCollider.h"

class GameEntity : public GameObject3D
{
public:
  GameEntity();
  virtual ~GameEntity();

public:
  virtual void OnAllocated();
  virtual void OnFree();
  
public:
  bool HitCheck(Collider3D* collider);

public:
  void SetHitRadius(T_FLOAT radius)
  {
    this->collider_->SetRadius(radius);
  }
  void SetEnabled(bool enabled)
  {
    this->is_enabled_ = enabled;
  }
  bool IsEnabled()
  {
    return this->is_enabled_;
  }
  GameEntityCollider* GetCollider()
  {
    return this->collider_;
  }

private:
  bool is_enabled_;

  GameEntityCollider* collider_;
};
#pragma once

#include <HalEngine.h>

#include "GameEntity.h"

class Bullet : public GameEntity, public IPoolAllocatable
{
public:
  Bullet();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

public:
  void Update() override;

public:
  inline bool IsAlive()
  {
    return this->lifetime_ > 0;
  }

public:
  inline void SetVelocity(const TVec3f& velocity)
  {
    this->velocity_ = velocity;
  }
  inline const TVec3f& GetVelocity() const
  {
    return this->velocity_;
  }

private:
  T_UINT16 lifetime_;
  TVec3f velocity_;
  Sprite3D* body_;

};
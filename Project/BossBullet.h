#pragma once

#include <HalEngine.h>

#include "GameEntity.h"

class BossBullet : public GameEntity, public IPoolAllocatable
{
public:
  BossBullet();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

public:
  void Update() override;
  void OnHited();

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
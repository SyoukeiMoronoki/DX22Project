#pragma once

#include <HalEngine.h>

#include "GameEntity.h"

class Star : public GameEntity, public IPoolAllocatable
{
public:
  Star();
  ~Star();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

private:
  GameObject3D* body_;

};
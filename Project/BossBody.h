#pragma once

#include <HalEngine.h>
#include "GameEntity.h"

class BossBody : public GameEntity, public IPoolAllocatable
{
public:
  BossBody();
  ~BossBody();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

public:
  void BodyUpdate(BossBody* front);

private:
  Sprite3D* body_;

};
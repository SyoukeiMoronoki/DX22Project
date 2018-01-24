#pragma once

#include <HalEngine.h>
#include "GameEntity.h"
#include "Player.h"

class BossBody : public GameEntity, public IPoolAllocatable
{
public:
  BossBody();
  ~BossBody();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

public:
  void BodyUpdate(BossBody* front, Player* player);

protected:
  void BodyMoveProcess(BossBody* front);

private:
  Sprite3D* body_;
  TVec3f rot_velocity_;
};
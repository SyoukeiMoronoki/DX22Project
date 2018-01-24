#pragma once

#include <HalEngine.h>
#include "GameEntity.h"
#include "Player.h"

class BossController;

class BossBody : public GameEntity, public IPoolAllocatable
{
public:
  BossBody();
  ~BossBody();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

public:
  void HeadUpdate(BossController* controller, Player* player);
  void BodyUpdate(BossController* controller, BossBody* front, Player* player);

protected:
  void UpdateProperties(BossController* controller, Player* player);

private:
  AnimatedSprite3D* body_;
};
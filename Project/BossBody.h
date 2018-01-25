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

public:
  void Move(TVec3f value);

public:
  inline const TVec3f& GetOldPosition() const
  {
    return this->old_position_;
  }

  inline const TVec3f GetMoveDirection() const
  {
    return this->move_direction_;
  }

private:
  AnimatedSprite3D* body_;
  TVec3f old_position_;
  TVec3f move_direction_;
};
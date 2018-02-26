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

  void OnDamaged();
  void OnWeakPointDamaged();

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

  inline bool IsWeak() const
  {
    return this->weak_flag_;
  }

private:
  AnimatedSprite3D* body_;
  Sprite3D* weak_point_sprite_;
  TVec3f old_position_;
  TVec3f move_direction_;
  bool weak_flag_;
};
#pragma once

#include <HalEngine.h>

#include "AllocatableGameEntityManager.h"
#include "BossBody.h"

class Player;
class Bullet;
class BossBrain;
class BossBulletManager;

class BossController : public AllocatableGameEntityManager<BossBody>
{
public:
  enum HitResult
  {
    NO_HIT,
    HIT_BODY,
    HIT_WEAK_POINT,
  };

public:
  BossController();
  ~BossController();

public:
  void Appear();
  void Update(Player* player);
  void ChangeBrain(BossBrain* brain, BossBody* head, Player* player);

  bool AttackToPlayer(Player* player);
  HitResult HitCheck(Bullet* bullet);

public:
  inline T_FLOAT GetSpeed() const
  {
    return this->speed_;
  }

  inline BossBrain* GetBrain() const
  {
    return this->brain_;
  }

  inline BossBody* GetHead() const
  {
    if (!this->enabled_)
    {
      return nullptr;
    }
    return const_cast<BossController*>(this)->Select([](BossBody* body) { return true; });
  }

  inline BossBulletManager* GetBulletManager() const
  {
    return this->bullets_;
  }

  inline bool IsEnabld() const
  {
    return this->enabled_;
  }

private:
  bool enabled_;

  T_UINT32 hp_;
  T_FLOAT speed_;
  BossBrain* brain_;
  BossBulletManager* bullets_;

};
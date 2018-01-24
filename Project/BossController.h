#pragma once

#include <HalEngine.h>

#include "AllocatableGameEntityManager.h"
#include "BossBody.h"

class Player;
class BossBrain;

class BossController : public AllocatableGameEntityManager<BossBody>
{
public:
  BossController();

public:
  void Update(Player* player);
  void ChangeBrain(BossBrain* brain, BossBody* head, Player* player);

public:
  inline T_FLOAT GetSpeed() const
  {
    return this->speed_;
  }

  inline BossBrain* GetBrain() const
  {
    return this->brain_;
  }

private:
  T_UINT32 hp_;
  T_FLOAT speed_;
  BossBrain* brain_;

};
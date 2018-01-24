#pragma once

#include <HalEngine.h>
#include "Player.h"
#include "BossBody.h"

class BossBrain
{
public:
  virtual void BrainUpdate(BossBody* self, Player* player) = 0;

};
#pragma once

#include "Player.h"

class ItemAttribute
{
public:
  virtual void OnHitToPlayer(Player* player) const = 0;
  
};
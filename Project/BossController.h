#pragma once

#include <HalEngine.h>

#include "AllocatableGameEntityManager.h"
#include "BossBody.h"

class Player;

class BossController : public AllocatableGameEntityManager<BossBody>
{
public:
  BossController();

public:
  void Update(Player* player);

private:


};
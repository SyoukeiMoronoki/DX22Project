#pragma once

#include "BossBrain.h"

namespace BossBrainTable
{

enum BrainKind
{
  BRAIN_CRAWL,
  BRAIN_CHASE,
  BRAIN_AROUND,
  BRAIN_JUMP,
  BRAIN_LANDING,
//  BRAIN_FLY,
//  BRAIN_FALL,
//  BRAIN_SHOT,
//  BRAIN_SHOT_STRONG,
//  BRAIN_SHOT_MANY,
//  BRAIN_GROUND_ATTACK,

  BRAIN_DATANUM,
};

BossBrain* GetBossBrain(T_UINT8 brain);

}
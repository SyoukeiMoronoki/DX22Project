#pragma once

#include "AttackData.h"

namespace AttackDataTable
{

enum AttackKind
{
  ATTACK_KIND_BOMB,

  ATTACK_KIND_DATANUM,
};

const AttackData* GetAttackData(AttackKind kind);

};
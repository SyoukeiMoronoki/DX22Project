#pragma once

#include "../Engine/NativeType.h"

namespace GameConstants
{

enum Phase
{
  PHASE_START,
  PHASE_ZAKO,
  PHASE_BOSS,
  PHASE_DARK,

  PHASE_DATANUM,
};

const T_UINT16 PHASE_TIMES[GameConstants::PHASE_DATANUM] =
{
  1500,
  3000,
  4000,
  2000,
};

T_UINT32 GetPhaseTime(T_UINT8 phase);

static const T_UINT16 HP_MAX = 1000;
static const T_UINT16 EYE_GAUGE_MAX = 3000;

static const T_FLOAT CAN_LOCKON_PROGRESS = 0.025f;
static const T_FLOAT CANT_LOCKON_PROGRESS = 0.025f;

}
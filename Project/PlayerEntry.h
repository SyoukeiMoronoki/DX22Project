#pragma once

#include "IPlayerController.h"
#include "IPlayerCamera.h"
#include "AnimalData.h"
#include "PlayerEntryDataModel.h"

class PlayerEntry
{
public:
  PlayerEntry(const PlayerEntryDataModel& model, IPlayerController* controller, IPlayerCamera* camera);
  PlayerEntry(T_UINT8 id, const AnimalData& animal_data, T_UINT8 handicap, IPlayerController* controller, IPlayerCamera* camera);
  ~PlayerEntry();

public:
  const T_UINT8 id;
  const AnimalData& animal_data;
  const T_UINT8 handicap;
  IPlayerController* const controller;
  IPlayerCamera* const camera;
};
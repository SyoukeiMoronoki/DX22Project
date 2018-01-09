#pragma once

#include "IPlayerCamera.h"

class ComputerCamera : public IPlayerCamera
{
public:
  virtual void RegisterToScene(Scene* scene) override;
  virtual void RegisterToPlayer(Player* player) override;
};
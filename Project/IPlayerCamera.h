#pragma once

#include <HalEngine.h>

class Player;

class IPlayerCamera : public GameObject3D
{
public:
  virtual ~IPlayerCamera() {}

public:
  virtual void RegisterToScene(Scene* scene) = 0;
  virtual void RegisterToPlayer(Player* player) = 0;
};
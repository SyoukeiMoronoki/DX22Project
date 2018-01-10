#pragma once

#include "IPlayerCamera.h"

class PlayerCamera : public IPlayerCamera
{
public:
  PlayerCamera();
  ~PlayerCamera();

public:
  void RegisterToScene(Scene* scene) override;
  void RegisterToPlayer(Player* player) override;
  void Update() override;

public:
  inline Camera3D_LookAt* GetCamera()
  {
    return this->camera_;
  }

private:
  Camera3D_LookAt* camera_;
};
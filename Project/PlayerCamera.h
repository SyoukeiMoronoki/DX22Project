#pragma once

#include "IPlayerCamera.h"

class PlayerCamera : public IPlayerCamera
{
public:
  PlayerCamera(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height);
  ~PlayerCamera();

public:
  void RegisterToScene(Scene* scene) override;
  void RegisterToPlayer(Player* player) override;
  void Update() override;

private:
  Camera3D_LookAt* camera_;
  INativeMatrix* translation_;
  INativeMatrix* scaling_;
};
#pragma once

#include "PlayerController.h"

class PlayerController_Walk : public PlayerController
{
public:
  PlayerController_Walk(Player* player);

protected:
  virtual void OnStart(const PlayerController* prev) override;
  virtual void OnEnd() override;

public:
  virtual void ControllProcess() override;
  virtual void OnAttack() override;

public:
  const TVec3f GetBulletDirection() const override;

private:
  Quaternion direction_quaternion_;
  Quaternion camera_quaternion_;
  TVec3f next_camera_pos_;
  TVec3f next_look_at_pos_;
  T_FLOAT camera_distance_;
  bool is_target_mode_;
  T_UINT8 target_double_tap_duration_;
};
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

};
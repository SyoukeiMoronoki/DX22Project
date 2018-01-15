#pragma once

#include "PlayerController.h"
#include "PlayerUI_Cursol.h"

class PlayerController_Scope : public PlayerController
{
public:
  PlayerController_Scope(Player* player);
  virtual ~PlayerController_Scope();

protected:
  virtual void OnStart(const PlayerController* prev) override;
  virtual void OnEnd() override;

public:
  virtual void ControllProcess() override;
  virtual void OnAttack() override;

public:
  inline const TVec3f GetBulletDirection() const override
  {
    return this->camera_->GetDirection();
  }

private:
  PlayerUI_Cursol* const cursol_;
  TVec3f look_at_pos_;
  Quaternion look_quaternion_;

};
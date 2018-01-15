#pragma once

#include <HalEngine.h>
class Player;

class PlayerController
{
public:
  PlayerController(Player* player);
  virtual ~PlayerController();

public:
  void Start(const PlayerController* prev);
  void End();
  virtual void ControllProcess() = 0;
  virtual void OnAttack() = 0;

protected:
  virtual void OnStart(const PlayerController* prev) = 0;
  virtual void OnEnd() = 0;

public:
  virtual const TVec3f GetBulletDirection() const = 0;
  inline const TVec3f& GetCameraPosition() const
  {
    return this->camera_->GetTransform()->GetPosition();
  }
  inline const TVec3f& GetCameraLookAtPosition() const
  {
    return this->camera_->GetLookAtPos();
  }

protected:
  Player* const player_;
  Camera3D_LookAt* const camera_;
  GameObject2D* const UIRoot_;
  
};
#pragma once

#include "PlayerInput.h"
#include "Attack.h"
#include "PlayerEntry.h"
#include "PlayerStatus.h"

class CardManager;
class CardFacade;

class Player : public GameEntity
{
public:
  Player(const PlayerEntry& entry);
  virtual ~Player();

public:
  void CardProcess(const PlayerInput& input, CardFacade* facade);

  virtual void PreUpdate() override;
  virtual void Update() override;

public:
  inline T_UINT8 GetID() const
  {
    return this->id_;
  }

  inline IPlayerController* GetController() const
  {
    return this->controller_;
  }

private:
  const T_UINT8 id_;
  PlayerStatus* const status_;
  IPlayerController* const controller_;
  Cube3D* body_;

  T_FLOAT speed_;
};

#pragma once

#include "IPlayerController.h"

class PlayerController : public IPlayerController
{
public:
  PlayerController(T_UINT8 id);

public:
  virtual void InputProcess(PlayerInput* dest) override;
  virtual T_UINT8 GetID() override;
  virtual bool IsComputer() override;

private:
  T_UINT8 id_;
};

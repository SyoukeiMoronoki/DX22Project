#pragma once

#include "PlayerInput.h"

class IPlayerController
{
public:
  IPlayerController();

public:
  virtual void InputProcess(PlayerInput* dest) = 0;
  void ControllProcess(PlayerInput* dest);

public:
  void AddControlDelay(T_UINT16 delay);
  void SetControlDelay(T_UINT16 delay);
  //�Œ���K�v�ȃf�B���C����́B���ɂ���ȏ�̃f�B���C������Ή������Ȃ�
  void SetControlDelayNegative(T_UINT16 delay);

public:
  virtual T_UINT8 GetID() = 0;
  virtual bool IsComputer() = 0;

private:
  T_UINT16 control_delay_;
  bool is_impacted_;
};
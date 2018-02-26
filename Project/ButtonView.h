#pragma once

#include <HalEngine.h>

#include "GameInput.h"

class ButtonView : public GameObject2D
{
public:
  enum ButtonID
  {
    BUTTON_A,
    BUTTON_S,
    BUTTON_D,
    BUTTON_W,

    BUTTON_K,
    BUTTON_L,
    BUTTON_SEMI,
    BUTTON_O,

    BUTTON_L_SHIFT,

    BUTTON_DATANUM,
  };

public:
  ButtonView(T_UINT8 button_id, T_FLOAT size);
  ~ButtonView();

public:
  void Update() override;
  
private:
  EntityModifierRoot* scale_modifier_;
  EntityModifierRoot* light_modifier_;

  T_UINT8 id_;
  Sprite* bg_;
  Sprite* light_;
  Sprite* char_;

};
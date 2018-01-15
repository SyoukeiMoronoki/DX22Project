#pragma once

#include <HalEngine.h>

#include "GameEntity.h"

class PlayerUI_Cursol : public GameObject2D
{
public:
  PlayerUI_Cursol();
  ~PlayerUI_Cursol();

public:
  void Update();
  void OnAttack();
    
private:
  T_UINT8 scaling_duration_;
  AnimatedSprite* sprite_;
  TVec2f position_;
  bool position_changed_;
};
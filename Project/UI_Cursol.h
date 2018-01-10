#pragma once

#include <HalEngine.h>

#include "GameEntity.h"

class UI_Cursol : public GameObject2D
{
public:
  UI_Cursol();
  ~UI_Cursol();

public:
  void GameInit();
  void Update();
  void UpdatePosition(const TVec2f& pos);
  void OnAttack();
    
private:
  T_UINT8 scaling_duration_;
  AnimatedSprite* sprite_;
  TVec2f position_;
  bool position_changed_;
};
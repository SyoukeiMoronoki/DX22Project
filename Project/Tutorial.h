#pragma once

#include <HalEngine.h>

class Tutorial : public GameObject2D
{
public:
  enum Kind
  {
    TUTORIAL_MOVE,
    TUTORIAL_SHIFT,
    TUTORIAL_SHOT,
    TUTORIAL_SCOPE,
    TUTORIAL_SONAR,
    TUTORIAL_SONAR_COMMENT,
    TUTORIAL_LOCK_ON,
    TUTORIAL_CANT_LOCK_ON,

    TUTORIAL_DATANUM
  };

public:
  Tutorial();
  ~Tutorial();

public:
  void Update() override;


private:
  AnimatedSprite* sprite_;
  EntityModifierRoot* modifier_;

  T_INT8 current_tutorial_;

  bool show_boss_message_;
  bool show_cant_target_message_;
};
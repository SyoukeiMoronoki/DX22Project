#pragma once

#include <HalEngine.h>

#include "GameSetting.h"

class GameDirector
{
public:
  inline static void GameStart(Scene* game_scene, const GameSetting* setting)
  {
    GameDirector::GetInstance()->GameStart_(game_scene, setting);
  }
  inline static void GameFinish()
  {
    GameDirector::GetInstance()->GameFinish_();
  }
  inline static const GameSetting& GetGameSetting()
  {
    return *GameDirector::GetInstance()->game_setting_;
  }
  inline static Scene* GetScene()
  {
    return GameDirector::GetInstance()->game_scene_;
  }

private:
  static GameDirector* GetInstance()
  {
    static GameDirector self;
    return &self;
  }
  GameDirector();
  GameDirector(const GameDirector&) {}

public:
  void GameStart_(Scene* game_scene, const GameSetting* setting);
  void GameFinish_();

private:
  const GameSetting* game_setting_;
  Scene* game_scene_;

  Color4F field_ambient_;
  Color4F field_fade_light_;

};
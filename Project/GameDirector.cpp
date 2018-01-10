#include "GameDirector.h"

GameDirector::GameDirector()
  : game_setting_(nullptr)
  , game_scene_(nullptr)
{}

void GameDirector::GameStart_(Scene* game_scene, const GameSetting* setting)
{
  //ŒÃ‚¢Ý’è‚ðíœ
  delete this->game_setting_;
  this->game_setting_ = setting;

  this->game_scene_ = game_scene;
  Director::GetInstance()->ChangeScene(game_scene);
}

void GameDirector::GameFinish_()
{
  delete this->game_setting_;
  this->game_setting_ = nullptr;
  this->game_scene_ = nullptr;
}

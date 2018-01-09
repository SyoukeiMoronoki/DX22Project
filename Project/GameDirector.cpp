#include "GameDirector.h"

GameDirector::GameDirector()
  : game_setting_(nullptr)
  , player_entries_()
  , game_scene_(nullptr)
{}

void GameDirector::GameStart_(Scene* game_scene, PlayerEntryDataModelList* player_models, const GameSetting* setting)
{
  //ŒÃ‚¢İ’è‚ğíœ
  delete this->game_setting_;
  this->game_setting_ = setting;

  this->game_scene_ = game_scene;
  //TODO:PlayerEntryListBuilder‚ÍPlayerEntryDataModelList‚ª‚Â‚×‚«‚Å‚Í?
  this->game_setting_->GetPlayerEntryListBuilder()->Build(player_models, &this->player_entries_);
  for (PlayerEntry* entry : this->player_entries_)
  {
    entry->camera->RegisterToScene(game_scene);
  }
  Director::GetInstance()->ChangeScene(game_scene);
}

void GameDirector::GameFinish_()
{
  delete this->game_setting_;
  this->game_setting_ = nullptr;
  this->game_scene_ = nullptr;
  for (PlayerEntry* entry : this->player_entries_)
  {
    delete entry;
  }
  this->player_entries_.clear();
}

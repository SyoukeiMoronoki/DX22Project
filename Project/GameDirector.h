#pragma once

#include <HalEngine.h>

#include "GameSetting.h"
#include "PlayerEntryDataModelList.h"
#include "PlayerEntry.h"

/*
  GameDirectorをシングルトンにした理由
  GameDirectorはゲームのルールに関わる部分であり、
  ゲーム中の殆どのオブジェクトがGameDirectorに依存するため
  グローバルなアクセスが可能になっても問題は少ない
  
  GameSettingをメンバにした理由
  ゲーム内の殆どのオブジェクトが参照するデータの為
  ゲーム中のアクセスはGetterを経由したconstアクセスだけに限定し、
  設定の変更を行う際はInit()を経由し、ゲームを再起動する。

  ゲームの開始もGameDirectorを経由させる事で、
  ゲームとの１対１対応である事を強調した。
*/

class GameDirector
{
public:
  inline static void GameStart(Scene* game_scene, PlayerEntryDataModelList* player_entry_models, const GameSetting* setting)
  {
    GameDirector::GetInstance()->GameStart_(game_scene, player_entry_models, setting);
  }
  inline static void GameFinish()
  {
    GameDirector::GetInstance()->GameFinish_();
  }
  inline static const GameSetting& GetGameSetting()
  {
    return *GameDirector::GetInstance()->game_setting_;
  }
  inline static const std::vector<PlayerEntry*>& GetPlayerEntries()
  {
    return GameDirector::GetInstance()->player_entries_;
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
  void GameStart_(Scene* game_scene, PlayerEntryDataModelList* player_models, const GameSetting* setting);
  void GameFinish_();

private:
  const GameSetting* game_setting_;
  std::vector<PlayerEntry*> player_entries_;
  Scene* game_scene_;

};
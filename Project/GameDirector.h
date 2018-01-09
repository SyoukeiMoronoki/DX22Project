#pragma once

#include <HalEngine.h>

#include "GameSetting.h"
#include "PlayerEntryDataModelList.h"
#include "PlayerEntry.h"

/*
  GameDirector���V���O���g���ɂ������R
  GameDirector�̓Q�[���̃��[���Ɋւ�镔���ł���A
  �Q�[�����̖w�ǂ̃I�u�W�F�N�g��GameDirector�Ɉˑ����邽��
  �O���[�o���ȃA�N�Z�X���\�ɂȂ��Ă����͏��Ȃ�
  
  GameSetting�������o�ɂ������R
  �Q�[�����̖w�ǂ̃I�u�W�F�N�g���Q�Ƃ���f�[�^�̈�
  �Q�[�����̃A�N�Z�X��Getter���o�R����const�A�N�Z�X�����Ɍ��肵�A
  �ݒ�̕ύX���s���ۂ�Init()���o�R���A�Q�[�����ċN������B

  �Q�[���̊J�n��GameDirector���o�R�����鎖�ŁA
  �Q�[���Ƃ̂P�΂P�Ή��ł��鎖�����������B
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
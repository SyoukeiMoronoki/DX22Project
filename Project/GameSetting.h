#pragma once

#include <vector>
#include <HalEngine.h>

#include "IPlayerEntryListBuilder.h"

#include "StarManager.h"

struct GameLevelParam
{
  //�����l�̂܂܂̗v�f������ƃG���[���o�͂����悤��
  GameLevelParam()
    : world_radius(0.0f)
    , star_levels(0)
    , gacha_star_count(0)
    , gacha_star_spawn_delay(0)
    , gacha_star_lifetime(0)
    , accel_weight(0.0f)
    , speed_weight(0.0f)
    , rot_speed_weight(0.0f)
    , power_weight(0.0f)
  {}

  //���_����F���̕ǂ܂ł̋���
  T_FLOAT world_radius;

  //���Ɋւ��郌�x���ϐ�
  StarManager::LevelParam star_levels;

  T_UINT16 gacha_star_count;
  T_UINT16 gacha_star_spawn_delay;
  T_UINT16 gacha_star_lifetime;

  //��蕨�̃X�e�[�^�X�ɂ�����d��
  T_FLOAT accel_weight;
  T_FLOAT speed_weight;
  T_FLOAT rot_speed_weight;
  T_FLOAT power_weight;
};

class GameSetting
{
public:
  GameSetting(IPlayerEntryListBuilder* entry_list_builder);
  ~GameSetting();

public:
  inline const GameLevelParam& GetLevelParam() const
  {
    return this->level_param_;
  }
  inline GameLevelParam& GetLevelParam()
  {
    return this->level_param_;
  }
  inline IPlayerEntryListBuilder* GetPlayerEntryListBuilder() const
  {
    return this->entry_list_builder_;
  }

private:
  GameLevelParam level_param_;
  IPlayerEntryListBuilder* entry_list_builder_;

};
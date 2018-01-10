#include "EnemyDataManager.h"

#include <stdlib.h>
#include "EnemyAttribute_Zako_1.h"
#include "EnemyAttribute_Zako_2.h"

enum EnemyKind
{
  ENEMY_KIND_ZAKO_1,
  ENEMY_KIND_ZAKO_2,

  ENEMY_KIND_DATANUM,
};

EnemyDataManager::EnemyDataManager()
{
  this->datas_ = new EnemyData*[ENEMY_KIND_DATANUM];
  //using namespace TextureResource;
  //this->SetEnemyData(ENEMY_KIND_ZAKO_1, PID_GAME, TID_GAME_ZAKO_1, TSizef(256.0f, 256.0f), "ウォーキングキメラ", new EnemyAttribute_Zako_1());
  //this->SetEnemyData(ENEMY_KIND_ZAKO_2, PID_GAME, TID_GAME_ZAKO_2, TSizef(256.0f, 256.0f), "キメラ", new EnemyAttribute_Zako_2());
}

EnemyDataManager::~EnemyDataManager()
{
}

void EnemyDataManager::GameInit()
{
}

void EnemyDataManager::SetEnemyData(T_UINT8 id, T_UINT8 pid, T_UINT16 tid, TSizef view_size, const char* name, IEnemyAttribute* attribute)
{
  this->datas_[id] = new EnemyData(id, pid, tid, view_size, name, attribute);
}

const EnemyData* EnemyDataManager::GetRandom() const
{
  return this->datas_[rand() % ENEMY_KIND_DATANUM];
}

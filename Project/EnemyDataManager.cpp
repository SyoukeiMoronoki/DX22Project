#include "EnemyDataManager.h"

#include <stdlib.h>
#include "EnemyAttribute_Zako_1.h"
#include "EnemyAttribute_Zako_2.h"
#include "Asset.h"

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
  this->SetEnemyData(ENEMY_KIND_ZAKO_1, Asset::Texture::ENEMY_ZAKO1,  TSizef(256.0f, 256.0f), "ウォーキングキメラ", 0.075f, new EnemyAttribute_Zako_1());
  this->SetEnemyData(ENEMY_KIND_ZAKO_2, Asset::Texture::ENEMY_ZAKO2,  TSizef(256.0f, 256.0f), "キメラ", 0.05f, new EnemyAttribute_Zako_2());
}

EnemyDataManager::~EnemyDataManager()
{
}

void EnemyDataManager::SetEnemyData(T_UINT8 id, const Texture& texture, TSizef view_size, const char* name, T_FLOAT speed, IEnemyAttribute* attribute)
{
  this->datas_[id] = new EnemyData(id, texture, view_size, name, speed, attribute);
}

const EnemyData* EnemyDataManager::GetRandom() const
{
  return this->datas_[rand() % ENEMY_KIND_DATANUM];
}

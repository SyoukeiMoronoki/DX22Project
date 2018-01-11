#pragma once

#include "EnemyData.h"

class EnemyDataManager
{
public:
  EnemyDataManager();
  ~EnemyDataManager();

private:
  void SetEnemyData(T_UINT8 id, const Texture& texture, TSizef view_size, const char* name, IEnemyAttribute* attribute);

public:
  void GameInit();
  const EnemyData* GetRandom() const;

private:
  EnemyData** datas_;
};
#pragma once

#include "EnemyData.h"

class EnemyDataManager
{
public:
  EnemyDataManager();
  ~EnemyDataManager();

private:
  void SetEnemyData(T_UINT8 id, T_UINT8 pid, T_UINT16 tid, TSizef view_size, const char* name, IEnemyAttribute* attribute);

public:
  void GameInit();
  const EnemyData* GetRandom() const;

private:
  EnemyData** datas_;
};
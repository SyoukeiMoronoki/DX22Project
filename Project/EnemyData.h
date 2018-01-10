#pragma once

#include <HalEngine.h>

#include "IEnemyAttribute.h"

class EnemyData
{
public:
  EnemyData(T_UINT8 id, T_UINT8 pid, T_UINT16 tid, TSizef view_size, const char* name, IEnemyAttribute* attribute)
    : id(id)
    , pid(pid)
    , tid(tid)
    , view_size(view_size)
    , name(name)
    , attribute(attribute)
  {}

  ~EnemyData()
  {
    delete attribute;
  }
  const T_UINT8 id;
  const T_UINT8 pid;
  const T_UINT16 tid;
  const TSizef view_size;
  const char* const name;
  const IEnemyAttribute* attribute;
};
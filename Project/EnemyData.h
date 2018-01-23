#pragma once

#include <HalEngine.h>

#include "IEnemyAttribute.h"

class EnemyData
{
public:
  EnemyData(T_UINT8 id, const Texture& texture, TSizef view_size, const char* name, T_FLOAT speed, IEnemyAttribute* attribute)
    : id(id)
    , texture(texture)
    , view_size(view_size)
    , name(name)
    , speed(speed)
    , attribute(attribute)
  {}

  ~EnemyData()
  {
    delete attribute;
  }
  const T_UINT8 id;
  const Texture& texture;
  const TSizef view_size;
  const char* const name;
  const T_FLOAT speed;
  const IEnemyAttribute* attribute;
};
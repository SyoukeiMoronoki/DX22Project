#pragma once

#include <HalEngine.h>

#include "IEnemyAttribute.h"

class EnemyData
{
public:
  EnemyData(T_UINT8 id, const Texture& texture, TSizef view_size, const char* name, IEnemyAttribute* attribute)
    : id(id)
    , texture(texture)
    , view_size(view_size)
    , name(name)
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
  const IEnemyAttribute* attribute;
};
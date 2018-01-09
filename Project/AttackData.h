#pragma once

#include <HalEngine.h>

#include "IAttackAttribute.h"

class AttackData
{
public:
  AttackData(T_UINT8 id, const char* name, T_UINT16 power, const Texture& texture, IAttackAttribute* attribute)
    : id(id)
    , name(name)
    , power(power)
    , texture(texture)
    , attribute(attribute)
  {}
  ~AttackData()
  {
    delete attribute;
  }
  const T_UINT8 id;
  const char* name;
  const T_UINT16 power;
  const Texture& texture;
  IAttackAttribute* const attribute;
};
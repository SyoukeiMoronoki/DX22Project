#pragma once

#include <HalEngine.h>

#include "ICardAttribute.h"

class CardData
{
public:
  CardData(T_UINT8 id, T_UINT8 cost, const char* name, const ICardAttribute* attribute)
    : id(id)
    , cost(cost)
    , name(name)
    , attribute(attribute)
  {}
  ~CardData()
  {
    delete attribute;
  }
  const T_UINT8 id;
  const T_UINT8 cost;
  const char* name;
  const ICardAttribute* attribute;
};



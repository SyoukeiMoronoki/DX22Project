#pragma once

#include <HalEngine.h>

#include "ItemAttribute.h"
#include "ItemAttribute_GodEnergy.h"

struct ItemData
{
  enum ItemKind
  {
    ITEM_KIND_GOD_ENERGY_0,
    ITEM_KIND_GOD_ENERGY_1,
    ITEM_KIND_GOD_ENERGY_2,

    ITEM_KIND_DATANUM,
  };

  static const ItemData& Create(ItemKind kind);

  ItemData(T_UINT8 id, T_FLOAT radius, T_UINT16 life_time, const char* name, ItemAttribute* attribute)
    : id(id)
    , radius(radius)
    , life_time(life_time)
    , name(name)
    , attribute(attribute)
  {}
  const T_UINT8 id;
  const T_FLOAT radius;
  const T_UINT16 life_time;
  const char* const name;
  const ItemAttribute* const attribute;
};
#include "ItemData.h"

static const ItemData ITEM_DATAS[ItemData::ITEM_KIND_DATANUM] =
{
  { ItemData::ITEM_KIND_GOD_ENERGY_0, 16.0f, 1000, "神エナジー小", new ItemAttribute_GodEnergy(50) },
  { ItemData::ITEM_KIND_GOD_ENERGY_1, 24.0f, 1000, "神エナジー中", new ItemAttribute_GodEnergy(250) },
  { ItemData::ITEM_KIND_GOD_ENERGY_2, 32.0f, 1000, "神エナジー大", new ItemAttribute_GodEnergy(1000) },
};

const ItemData& ItemData::Create(ItemKind kind)
{
  return ITEM_DATAS[kind];
}

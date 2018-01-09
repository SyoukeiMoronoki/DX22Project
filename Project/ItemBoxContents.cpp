#include "ItemBoxContents.h"

//TODO:óvêÆóù

static const ItemBoxContentsElement ELEMENTS_COMMON[] =
{
  { ItemData::ITEM_KIND_GOD_ENERGY_0, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_1, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_2, 10 },

  { ItemData::ITEM_KIND_DATANUM, 0 },
};

static const ItemBoxContentsElement ELEMENTS_TIME[] =
{
  { ItemData::ITEM_KIND_GOD_ENERGY_0, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_1, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_2, 10 },

  { ItemData::ITEM_KIND_DATANUM, 0 },
};

static const ItemBoxContentsElement ELEMENTS_SPACE[] =
{
  { ItemData::ITEM_KIND_GOD_ENERGY_0, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_1, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_2, 10 },

  { ItemData::ITEM_KIND_DATANUM, 0 },
};

static const ItemBoxContentsElement ELEMENTS_POWER[] =
{
  { ItemData::ITEM_KIND_GOD_ENERGY_0, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_1, 10 },
  { ItemData::ITEM_KIND_GOD_ENERGY_2, 10 },

  { ItemData::ITEM_KIND_DATANUM, 0 },
};

static const ItemBoxContents ITEM_BOX_CONTENTS[ItemBoxContents::BOX_CONTENTS_DATANUM] =
{
  { ItemBoxContents::BOX_CONTENTS_COMMON, ELEMENTS_COMMON, 2, 7 },
  { ItemBoxContents::BOX_CONTENTS_TIME, ELEMENTS_TIME, 2, 7 },
  { ItemBoxContents::BOX_CONTENTS_SPACE, ELEMENTS_SPACE, 2, 7 },
  { ItemBoxContents::BOX_CONTENTS_POWER, ELEMENTS_POWER, 2, 7 },
};

struct ItemBoxContentsGeneratorElement
{
  ItemBoxContentsGeneratorElement(ItemBoxContents::ItemBoxContentsID id, T_UINT8 weight)
    : id(id)
    , weight(weight)
  {}
  ItemBoxContents::ItemBoxContentsID id;
  T_UINT8 weight;
};

static const ItemBoxContentsGeneratorElement ITEM_BOX_CONTENTS_GENERATE_TABLE[ItemBoxContents::BOX_CONTENTS_DATANUM]
{
  { ItemBoxContents::BOX_CONTENTS_COMMON, 30 },
  { ItemBoxContents::BOX_CONTENTS_TIME, 10 },
  { ItemBoxContents::BOX_CONTENTS_SPACE, 10 },
  { ItemBoxContents::BOX_CONTENTS_POWER, 10 },
};

static T_UINT16 ITEM_BOX_CONTENTS_TABLE_WEIGHT_SUM = 0;

const ItemBoxContents* ItemBoxContents::Generate()
{
  if (ITEM_BOX_CONTENTS_TABLE_WEIGHT_SUM == 0)
  {
    for (T_UINT8 i = 0; i < ItemBoxContents::BOX_CONTENTS_DATANUM; ++i)
    {
      ITEM_BOX_CONTENTS_TABLE_WEIGHT_SUM += ITEM_BOX_CONTENTS_GENERATE_TABLE[i].weight;
    }
  }
  T_UINT16 hit = rand() % ITEM_BOX_CONTENTS_TABLE_WEIGHT_SUM;
  for (T_UINT8 i = 0; i < ItemBoxContents::BOX_CONTENTS_DATANUM; ++i)
  {
    if (hit < ITEM_BOX_CONTENTS_GENERATE_TABLE[i].weight)
    {
      return &ITEM_BOX_CONTENTS[ITEM_BOX_CONTENTS_GENERATE_TABLE[i].id];
    }
    hit -= ITEM_BOX_CONTENTS_GENERATE_TABLE[i].weight;
  }
  return nullptr;
}

ItemBoxContents::ItemBoxContents(ItemBoxContentsID id, const ItemBoxContentsElement* elements, T_UINT8 generate_min, T_UINT8 generate_max)
  : id_(id)
  , elements_(elements)
  , generate_min_(generate_min)
  , generate_max_(generate_max)
{
  const ItemBoxContentsElement* e = elements;
  T_UINT8 count = 0;
  T_UINT16 weight_sum = 0;
  while (e->kind != ItemData::ITEM_KIND_DATANUM)
  {
    weight_sum += e->weight;
    e++;
    count++;
  }
  this->weight_sum_ = weight_sum;
  this->elements_count_ = count;
}

ItemData::ItemKind ItemBoxContents::GenerateItem() const
{
  const ItemBoxContentsElement* e = this->elements_;
  T_UINT16 hit = rand() % this->weight_sum_;
  while (e->kind != ItemData::ITEM_KIND_DATANUM)
  {
    if (hit < e->weight)
    {
      return e->kind;
    }
    hit -= e->weight;
    e++;
  }
  return ItemData::ITEM_KIND_DATANUM;
}

T_UINT8 ItemBoxContents::GenerateItemCount() const
{
  return (rand() % (generate_max_ - generate_min_)) + generate_min_;
}

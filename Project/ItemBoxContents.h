#pragma once

#include "ItemData.h"

struct ItemBoxContentsElement
{
  ItemBoxContentsElement(ItemData::ItemKind kind, T_UINT8 weight)
    : kind(kind)
    , weight(weight)
  {}
  ItemData::ItemKind kind;
  T_UINT8 weight;
};

class ItemBoxContents
{
public:
  enum ItemBoxContentsID
  {
    BOX_CONTENTS_COMMON,
    BOX_CONTENTS_TIME,
    BOX_CONTENTS_SPACE,
    BOX_CONTENTS_POWER,

    BOX_CONTENTS_DATANUM,
  };

  static const ItemBoxContents* Generate();

public:
  //ItemBoxContentsElement* elements ‚Í
  //ÅŒã”ö‚Ékind‚ðItemData::ITEM_KIND_DATANUM‚Æ‚µ‚½‚à‚Ì‚ð“ü‚ê‚é
  ItemBoxContents(ItemBoxContentsID id, const ItemBoxContentsElement* elements, T_UINT8 generate_min, T_UINT8 generate_max);

public:
  ItemData::ItemKind GenerateItem() const;
  T_UINT8 GenerateItemCount() const;

public:
  inline ItemBoxContentsID GetID() const
  {
    return this->id_;
  }

private:
  const ItemBoxContentsID id_;
  const ItemBoxContentsElement* const elements_;
  const T_UINT8 generate_min_;
  const T_UINT8 generate_max_;
  T_UINT8 elements_count_;
  T_UINT16 weight_sum_;
};

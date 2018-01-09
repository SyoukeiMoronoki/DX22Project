#pragma once

#include "ItemAttribute.h"

class ItemAttribute_GodEnergy : public ItemAttribute {
public:
  ItemAttribute_GodEnergy(T_UINT16 value);

public:
  virtual void OnHitToPlayer(Player* player) const override;

private:
  const T_UINT16 value_;
};
#include "ItemAttribute_GodEnergy.h"

ItemAttribute_GodEnergy::ItemAttribute_GodEnergy(T_UINT16 value)
  : value_(value)
{}

void ItemAttribute_GodEnergy::OnHitToPlayer(Player* player) const
{
  //player->AddGodEnergy(this->value_);
}

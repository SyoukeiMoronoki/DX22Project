#include "CardAttribute_Trap.h"

CardAttribute_Trap::CardAttribute_Trap(T_FLOAT throw_length, T_FLOAT radius)
  : throw_length_(throw_length)
  , radius_(radius)
{}

void CardAttribute_Trap::OnUse(CardFacade* facade) const
{
  facade->Player_ThrowTrap(this->throw_length_, this->radius_);
}

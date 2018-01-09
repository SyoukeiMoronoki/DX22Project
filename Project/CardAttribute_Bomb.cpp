#include "CardAttribute_Bomb.h"

CardAttribute_Bomb::CardAttribute_Bomb(T_FLOAT throw_length, T_FLOAT radius)
  : throw_length_(throw_length)
  , radius_(radius)
{}

void CardAttribute_Bomb::OnUse(CardFacade* facade) const
{
  facade->Player_ThrowBomb(this->throw_length_, this->radius_);
}
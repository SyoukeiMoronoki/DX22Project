#include "CardAttribute_Booster.h"

CardAttribute_Booster::CardAttribute_Booster(T_FLOAT speed, T_UINT8 delay)
  : speed_(speed)
  , delay_(delay)
{}

void CardAttribute_Booster::OnUse(CardFacade* facade) const
{
  facade->Player_Boost(this->speed_, this->delay_);
}

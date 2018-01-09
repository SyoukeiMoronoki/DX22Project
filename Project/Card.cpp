#include "Card.h"

Card::Card(const CardData* data)
  : data_(data)
{
}

void Card::OnUse(CardFacade* facade)
{
  this->data_->attribute->OnUse(facade);
}

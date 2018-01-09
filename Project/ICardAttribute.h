#pragma once

#include "CardFacade.h"

class ICardAttribute
{
public:
  virtual void OnUse(CardFacade* facade) const = 0;
};
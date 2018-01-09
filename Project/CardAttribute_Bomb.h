#pragma once

#include "ICardAttribute.h"

class CardAttribute_Bomb : public ICardAttribute
{
public:
  CardAttribute_Bomb(T_FLOAT throw_length, T_FLOAT radius);

public:
  virtual void OnUse(CardFacade* facade) const override;

private:
  const T_FLOAT throw_length_;
  const T_FLOAT radius_;
};

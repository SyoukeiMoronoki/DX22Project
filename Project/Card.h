#pragma once

#include <HalEngine.h>

#include "CardData.h"
#include "CardFacade.h"

class Card
{
public:
  Card(const CardData* data);
  ~Card() {}

  void OnUse(CardFacade* facade);

public:
  inline const CardData* GetData() const
  {
    return this->data_;
  }
  inline T_UINT8 GetCost() const
  {
    return this->data_->cost;
  }

private:
  const CardData* data_;
};
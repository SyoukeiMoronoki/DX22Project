#pragma once

#include <HalEngine.h>
#include "ICardAttribute.h"

//OnUseイベントをCard_Attributeに移譲し、Cardへのコンポジションとする

class CardAttribute_Booster : public ICardAttribute
{
public:
  CardAttribute_Booster(T_FLOAT speed, T_UINT8 delay);

  virtual void OnUse(CardFacade* facade) const override;

private:
  const T_FLOAT speed_;
  const T_UINT8 delay_;
};
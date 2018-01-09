#pragma once

#include <HalEngine.h>
#include "ICardAttribute.h"

//OnUse�C�x���g��Card_Attribute�Ɉڏ����ACard�ւ̃R���|�W�V�����Ƃ���

class CardAttribute_Booster : public ICardAttribute
{
public:
  CardAttribute_Booster(T_FLOAT speed, T_UINT8 delay);

  virtual void OnUse(CardFacade* facade) const override;

private:
  const T_FLOAT speed_;
  const T_UINT8 delay_;
};
#pragma once

#include <HalEngine.h>
#include "IAttackAttribute.h"

class AttackAttribute_Bomb : public IAttackAttribute
{
public:
  AttackAttribute_Bomb(T_FLOAT radius, T_FLOAT throw_power);

public:
  virtual void OnAttach(AttackFacade_Attach* facade) const override;
  virtual void OnDetach(AttackFacade* facade) const override;
  virtual bool OnUpdate(AttackFacade* facade) const override;

private:
  const T_FLOAT radius_;
  const T_FLOAT throw_power_;

};

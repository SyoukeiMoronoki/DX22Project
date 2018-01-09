#pragma once

class AttackFacade_Attach;
class AttackFacade;

class IAttackAttribute
{
public:
  virtual void OnAttach(AttackFacade_Attach* facade) const = 0;
  virtual void OnDetach(AttackFacade* facade) const = 0;
  virtual bool OnUpdate(AttackFacade* facade) const = 0;
};

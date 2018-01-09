#pragma once

#include <HalEngine.h>

#include "GameEntity.h"
#include "AttackData.h"

class IAttackAttribute;

class Attack : public GameEntity
{
public:
  Attack();
  ~Attack();

public:
  void Update(AttackFacade* facade);
  void Spawn(const AttackData* data, AttackFacade_Attach* facade);
  
public:
  inline const AttackData* GetAttackData() const
  {
    return this->data_;
  }

private:
  const AttackData* data_;

};

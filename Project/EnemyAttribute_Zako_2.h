#pragma once

#include "IEnemyAttribute.h"

class EnemyAttribute_Zako_2 : public IEnemyAttribute
{
  // IEnemyAttribute ����Čp������܂���
  virtual void OnAttached(Enemy* enemy) const;
  virtual void OnUpdate(Enemy* enemy) const;
  virtual void OnDamaged(Enemy* enemy) const;
};
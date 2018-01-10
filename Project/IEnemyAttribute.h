#pragma once


class Enemy;

class IEnemyAttribute
{
public:
  virtual void OnAttached(Enemy* enemy) const = 0;
  virtual void OnUpdate(Enemy* enemy) const = 0;
  virtual void OnDamaged(Enemy* enemy) const = 0;

};
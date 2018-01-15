#pragma once

#include "../Engine/NativeType.h"

#include "AllocatableGameEntityManager.h"
#include "EnemyDataManager.h"
#include "Enemy.h"

class Player;
class Bullet;

class EnemyManager : public AllocatableGameEntityManager<Enemy>
{
public:
  EnemyManager(T_UINT8 enemy_max);

public:
  void Update(bool is_sonar);
  void OnDamaged();

  bool HitCheck(Bullet* bullet);
  bool AttackToPlayer(Player* player);

public:
  Enemy* SpawnToRandomPosition(Player* player);

private:
  EnemyDataManager* data_manager_;

};
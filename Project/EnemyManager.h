#pragma once

#include "../Engine/NativeType.h"

#include "AllocatableGameEntityManager.h"
#include "EnemyDataManager.h"
#include "Enemy.h"
#include "EnemyBulletManager.h"

class Player;
class Bullet;

class EnemyManager : public AllocatableGameEntityManager<Enemy>
{
public:
  EnemyManager(T_UINT8 enemy_max);

public:
  void Update(Player* player);
  void OnDamaged();

  bool HitCheck(Bullet* bullet);
  bool AttackToPlayer(Player* player);

public:
  Enemy* SpawnToRandomPosition(Player* player);

public:
  inline EnemyBulletManager* GetBulletManager()
  {
    return this->enemy_bullet_manager_;
  }

private:
  EnemyDataManager* data_manager_;
  EnemyBulletManager* enemy_bullet_manager_;

};
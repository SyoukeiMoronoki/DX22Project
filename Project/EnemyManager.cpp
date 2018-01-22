#include "EnemyManager.h"

#include <stdlib.h>
#include "EnemyData.h"
#include "Player.h"

EnemyManager::EnemyManager(T_UINT8 enemy_max)
  : AllocatableGameEntityManager<Enemy>(enemy_max)
{
  this->data_manager_ = new EnemyDataManager();
}

void EnemyManager::Update(bool is_sonar)
{
  this->Loop([&](Enemy* enemy)
  {
    enemy->EnemyUpdate(is_sonar);
  });
  std::deque<Enemy*> dead_enemies = std::deque<Enemy*>();
  this->SelectAll(&dead_enemies, [](Enemy* enemy)
  {
    return !enemy->IsAlive();
  });
  for (Enemy* enemy : dead_enemies)
  {
    this->Free(enemy);
  }
}

void EnemyManager::OnDamaged()
{
  this->Loop([&](Enemy* enemy)
  {
    enemy->OnDamaged();
  });
}

bool EnemyManager::HitCheck(Bullet* bullet)
{
  return true;
}

bool EnemyManager::AttackToPlayer(Player* player)
{
  bool damaged = false;
  Enemy* enemy = this->Collision(player->GetCollider());
  if (enemy)
  {
    player->AddDamage();
    damaged = true;
  }
  return damaged;
}

//bool EnemyManager::CollisionProcess(ICircleCollider* collider)
//{
//  bool weak_hit = false;
//  EnemyDamageFacade facade;
//  for (T_UINT16 i = 0; i < this->size_; ++i)
//  {
//    Enemy* enemy = ((Enemy*)this->pool_[i]);
//    if (!enemy->IsEnabled())
//    {
//      continue;
//    }
//    if (enemy->WeakPointHitCheck(collider))
//    {
//      enemy->OnWeakPointDamaged(facade);
//      weak_hit = true;
//      continue;
//    }
//    if (!enemy->HitCheck(collider))
//    {
//      continue;
//    }
//    enemy->OnDamaged(facade);
//  }
//  return weak_hit;
//}

Enemy* EnemyManager::SpawnToRandomPosition(Player* player)
{
  Enemy* enemy = (Enemy*)this->Allocate();
  if (!enemy)
  {
    return nullptr;
  }
  TVec3f pos = player->GetTransform()->GetPosition();
  T_FLOAT range = 10.0f;
  enemy->GetTransform()->SetX(pos.x + Util::GetRandom(-range, range));
  enemy->GetTransform()->SetZ(pos.z + Util::GetRandom(-range, range));
  enemy->Spawn(this->data_manager_->GetRandom());
  return enemy;
}

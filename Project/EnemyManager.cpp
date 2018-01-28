#include "EnemyManager.h"

#include <stdlib.h>
#include "EnemyData.h"
#include "Player.h"

EnemyManager::EnemyManager(T_UINT8 enemy_max)
  : AllocatableGameEntityManager<Enemy>(enemy_max)
{
  this->data_manager_ = new EnemyDataManager();
  this->enemy_bullet_manager_ = new EnemyBulletManager(enemy_max * 2);
  const T_UINT16 depth = 2;
  const T_UINT16 round_max = enemy_max / depth;
  T_UINT8 round_count = 0;
  const T_FLOAT rad_d = MathConstants::PI_2 / round_max;
  T_FLOAT rad_offset = 0.0f;
  const T_FLOAT length_d = 2.0f;
  T_FLOAT length_offset = 5.0f;
  this->LoopIncludingPool([&](Enemy* enemy)
  {
    enemy->SetHomingPos(rad_offset + rad_d * round_count, length_offset);
    enemy->SetEnemyBulletManager(this->enemy_bullet_manager_);
    round_count++;
    if (round_count == round_max)
    {
      round_count = 0;
      length_offset += length_d;
    }
  });
}

EnemyManager::~EnemyManager()
{
  delete this->enemy_bullet_manager_;
  delete this->data_manager_;
}

void EnemyManager::Update(Player* player)
{
  this->enemy_bullet_manager_->Update();
  this->Loop([&](Enemy* enemy)
  {
    enemy->EnemyUpdate(player);
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

EnemyManager::HitResult EnemyManager::HitCheck(Bullet* bullet)
{
  Enemy* hit_enemy = this->Select([&](Enemy* enemy)
  {
    return enemy->WeakPointHitCheck(bullet->GetCollider());
  });
  if (hit_enemy)
  {
    hit_enemy->OnWeakPointDamaged();
    return HitResult::HIT_WEAK_POINT;
  }
  hit_enemy = this->Select([&](Enemy* enemy)
  {
    return enemy->HitCheck(bullet->GetCollider());
  });
  if (hit_enemy)
  {
    hit_enemy->OnDamaged();
    return HitResult::HIT_BODY;
  }
  return HitResult::NO_HIT;
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
  if (!damaged)
  {
    EnemyBullet* bullet = this->enemy_bullet_manager_->Collision(player->GetCollider());
    if (bullet)
    {
      player->AddDamage();
      damaged = true;
    }
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

#include "EnemyBulletManager.h"

EnemyBulletManager::EnemyBulletManager(T_UINT16 count)
  : AllocatableGameEntityManager(count)
{
}

void EnemyBulletManager::Update()
{
  std::deque<EnemyBullet*> dead_bullets_ = std::deque<EnemyBullet*>();
  this->SelectAll(&dead_bullets_, [](EnemyBullet* bullet)
  {
    return !bullet->IsAlive();
  });
  for (EnemyBullet* bullet : dead_bullets_)
  {
    this->Free(bullet);
  }
}

void EnemyBulletManager::Emmision(GameObject3D* emmitter, GameObject3D* target)
{
  EnemyBullet* bullet = this->Allocate();
  if (!bullet)
  {
    return;
  }
  TVec3f emmitter_world_pos = emmitter->GetTransform()->GetWorldPosition();
  TVec3f target_world_pos = target->GetTransform()->GetWorldPosition();
  emmitter_world_pos.y = target_world_pos.y;
  bullet->GetTransform()->SetPosition(emmitter_world_pos);
  TVec3f dir = target_world_pos - emmitter_world_pos;
  bullet->SetVelocity(dir.Normalized() * 0.1f);
}

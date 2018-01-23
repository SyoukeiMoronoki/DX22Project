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
  bullet->GetTransform()->SetPosition(emmitter->GetTransform()->GetWorldPosition());
  TVec3f dir = target->GetTransform()->GetWorldPosition() - emmitter->GetTransform()->GetWorldPosition();
  bullet->SetVelocity(dir.Normalized() * 0.1f);
}

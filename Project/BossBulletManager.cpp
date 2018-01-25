#include "BossBulletManager.h"

BossBulletManager::BossBulletManager(T_UINT16 count)
  : AllocatableGameEntityManager(count)
{
}

void BossBulletManager::Update()
{
  std::deque<BossBullet*> dead_bullets_ = std::deque<BossBullet*>();
  this->SelectAll(&dead_bullets_, [](BossBullet* bullet)
  {
    return !bullet->IsAlive();
  });
  for (BossBullet* bullet : dead_bullets_)
  {
    this->Free(bullet);
  }
}

void BossBulletManager::Emmision(GameObject3D * emmitter, GameObject3D * target)
{
  BossBullet* bullet = this->Allocate();
  if (!bullet)
  {
    return;
  }
  TVec3f emmitter_world_pos = emmitter->GetTransform()->GetWorldPosition();
  TVec3f target_world_pos = target->GetTransform()->GetWorldPosition();
  emmitter_world_pos.y = target_world_pos.y;
  bullet->GetTransform()->SetPosition(emmitter_world_pos);
  TVec3f dir = target_world_pos - emmitter_world_pos;
  bullet->SetVelocity(dir.Normalized() * 0.5f);
}

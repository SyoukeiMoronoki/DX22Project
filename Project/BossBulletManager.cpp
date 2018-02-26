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

void BossBulletManager::Emmision(const TVec3f emmitter_pos, const TVec3f target_pos)
{
  BossBullet* bullet = this->Allocate();
  if (!bullet)
  {
    return;
  }
  bullet->GetTransform()->SetPosition(emmitter_pos);
  TVec3f dir = target_pos - emmitter_pos;
  bullet->SetVelocity(dir.Normalized() * 1.5f);
}

#include "BulletManager.h"

BulletManager::BulletManager(T_UINT16 count)
  : AllocatableGameEntityManager(count)
{
}

void BulletManager::Update()
{
  std::deque<Bullet*> dead_bullets_ = std::deque<Bullet*>();
  this->SelectAll(&dead_bullets_, [](Bullet* bullet)
  {
    return !bullet->IsAlive();
  });
  for (Bullet* bullet : dead_bullets_)
  {
    this->Free(bullet);
  }
}

void BulletManager::Emmision(GameObject3D* emmitter, const TVec3f& direction)
{
  Bullet* bullet = this->Allocate();
  if (!bullet)
  {
    return;
  }
  //TODO:@‹O“¹‚ª‚¨‚©‚µ‚¢
  bullet->GetTransform()->SetPosition(emmitter->GetTransform()->GetWorldPosition());
  TVec3f dir = direction;
  dir.x *= -1.0f;
  dir.y *= -1.0f;
  bullet->SetVelocity(dir);
  //bullet->SetVelocity(emmitter->GetTransform()->GetDirection());
}

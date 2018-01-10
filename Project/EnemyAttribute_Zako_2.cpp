#include "EnemyAttribute_Zako_2.h"
#include "GameSceneDirector.h"

#include "Enemy.h"

static const char* ZAKO2_COLLIDER = "Zako2_Collider";

void EnemyAttribute_Zako_2::OnAttached(Enemy* enemy) const
{
  GameSceneDirector* director = &GameSceneDirector::GetInstance();
  //GameEntityCollider_Circle* head = director->GetColliderAllocator()->AllocateCircle();
  //head->SetLocalPosition(0.0f, -25.0f);
  //head->SetRadius(64);
  //enemy->AddCollider(head);

  //GameEntityCollider_Circle* weak = director->GetColliderAllocator()->AllocateCircle();
  //weak->SetLocalPosition(rand() % 60 - 30.0f, rand() % 60 - 30.0f - 25.0f);
  //weak->SetRadius(5);
  //enemy->SetWeakPoint(weak);
}

void EnemyAttribute_Zako_2::OnUpdate(Enemy* enemy) const
{
  enemy->MoveRadialRate(-0.00075f);
}

void EnemyAttribute_Zako_2::OnDamaged(Enemy* enemy) const
{
  enemy->MoveRadialRate(0.1f);
}

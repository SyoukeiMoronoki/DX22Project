#include "EnemyAttribute_Zako_1.h"
#include "GameSceneDirector.h"
#include <stdlib.h>

#include "Enemy.h"

static const char* ZAKO1_COLLIDER = "Zako1_Collider";

void EnemyAttribute_Zako_1::OnAttached(Enemy* enemy) const
{
  GameSceneDirector* director = &GameSceneDirector::GetInstance();
  //GameEntityCollider_Circle* head = director->GetColliderAllocator()->AllocateCircle();
  //head->SetLocalPosition(0.0f, 35.0f);
  //head->SetRadius(41);
  //enemy->AddCollider(head);
  //GameEntityCollider_Rect* left = director->GetColliderAllocator()->AllocateRect();
  //left->SetLocalPosition(-36.0f, -64.0f);
  //left->SetWidth(10);
  //left->SetHeight(64);
  //enemy->AddCollider(left);
  //GameEntityCollider_Rect* right = director->GetColliderAllocator()->AllocateRect();
  //right->SetLocalPosition(36.0f, -64.0f);
  //right->SetWidth(10);
  //right->SetHeight(64);
  //enemy->AddCollider(right);

  //GameEntityCollider_Circle* weak = director->GetColliderAllocator()->AllocateCircle();
  //weak->SetLocalPosition(rand() % 60 - 30.0f, rand() % 60 - 30.0f + 35.0f);
  //weak->SetRadius(5);
  //enemy->SetWeakPoint(weak);
}

void EnemyAttribute_Zako_1::OnUpdate(Enemy* enemy) const
{
  enemy->MoveRadialRate(-0.00075f);
  if (enemy->GetCount() % 300 < 150)
  {
    enemy->MoveTangential(5);
  }
  else
  {
    enemy->MoveTangential(-5);
  }
}

void EnemyAttribute_Zako_1::OnDamaged(Enemy* enemy) const
{
  enemy->MoveRadialRate(0.1f);
}

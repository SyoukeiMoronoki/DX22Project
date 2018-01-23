#include "BossController.h"

static const T_UINT8 BOSS_BODY_COUNT = 3;

BossController::BossController()
  : AllocatableGameEntityManager(BOSS_BODY_COUNT)
{
  for (T_UINT8 i = 0; i < BOSS_BODY_COUNT; ++i)
  {
    BossBody* body = this->Allocate();
    body->GetTransform()->SetY(10.0f);
  }
}

void BossController::Update(Player* player)
{
  BossBody* front = nullptr;
  this->Loop([&](BossBody* body)
  {
    body->BodyUpdate(front);
    front = body;
  });
}

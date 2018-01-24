#include "BossController.h"
#include "BossBrain.h"
#include "BossBrainTable.h"

static const T_UINT8 BOSS_BODY_COUNT = 30;
static const T_FLOAT SPEED = 0.4f;

BossController::BossController()
  : AllocatableGameEntityManager(BOSS_BODY_COUNT)
{
  for (T_UINT8 i = 0; i < BOSS_BODY_COUNT; ++i)
  {
    BossBody* body = this->Allocate();
    body->GetTransform()->SetY(10.0f);
  }
  this->speed_ = SPEED;
  this->brain_ = nullptr;
}

void BossController::Update(Player* player)
{
  BossBody* head = this->Select([](BossBody*) { return true; });
  if (!this->brain_)
  {
    this->ChangeBrain(BossBrainTable::GetBossBrain(BossBrainTable::BRAIN_CRAWL), head, player);
  }
  head->HeadUpdate(this, player);

  BossBody* front = head;
  this->Loop([&](BossBody* body)
  {
    if (body == head)
    {
      return;
    }
    body->BodyUpdate(this, front, player);
    front = body;
  });
}

void BossController::ChangeBrain(BossBrain* brain, BossBody* head, Player* player)
{
  this->brain_ = brain;
  this->brain_->Init(this, head, player);
}

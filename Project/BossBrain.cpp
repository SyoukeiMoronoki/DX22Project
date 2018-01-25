#include "BossBrain.h"
#include "BossBrainTable.h"

BossBrain::BossBrain()
  : count_(0)
{
}

void BossBrain::Init(BossController* controller, BossBody* head, Player* player)
{
  this->count_ = 0;
  this->BrainInit(controller, head, player);
}

void BossBrain::Update(BossController* controller, BossBody* head, Player* player)
{
  this->BrainUpdate(controller, head, player);
  T_INT8 id = this->BrainChange(this->count_, controller, head, player);
  if (head->GetTransform()->GetY() > 80.0f)
  {
    id = BossBrainTable::BRAIN_CHASE;
  }
  if (id != -1)
  {
    controller->ChangeBrain(BossBrainTable::GetBossBrain(id), head, player);
    return;
  }
  this->count_++;
}

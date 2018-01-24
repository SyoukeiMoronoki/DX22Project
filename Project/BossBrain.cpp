#include "BossBrain.h"
#include "BossBrainTable.h"

BossBrain::BossBrain()
  : count_(0)
{
}

void BossBrain::Init(BossController* controller, BossBody* head, Player* player)
{
  this->BrainInit(controller, head, player);
}

void BossBrain::Update(BossController* controller, BossBody* head, Player* player)
{
  if (this->count_ == 0)
  {
    this->BrainInit(controller, head, player);
  }
  this->BrainUpdate(controller, head, player);
  T_INT8 id = this->BrainChange(this->count_);
  if (id != -1)
  {
    controller->ChangeBrain(BossBrainTable::GetBossBrain(id), head, player);
  }
  this->count_++;
}

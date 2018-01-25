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
  TVec3f distance = player->GetTransform()->GetWorldPosition() - head->GetTransform()->GetWorldPosition();
  T_FLOAT distance_length = distance.Length();
  if (head->GetTransform()->GetY() > 50.0f)
  {
    T_UINT8 rand = Util::GetRandom(0, 9);
    if (rand < 9)
    {
      id = BossBrainTable::BRAIN_LANDING;
    }
    else
    {
      id = BossBrainTable::BRAIN_CHASE;
    }
  }
  else if (distance_length > 50.0f)
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

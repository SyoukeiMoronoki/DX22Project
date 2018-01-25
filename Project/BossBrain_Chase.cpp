#include "BossBrain_Chase.h"
#include "BossBrainTable.h"

void BossBrain_Chase::BrainInit(BossController* controller, BossBody* head, Player* player)
{
}

void BossBrain_Chase::BrainUpdate(BossController* controller, BossBody* head, Player* player)
{
  TVec3f distance = player->GetTransform()->GetWorldPosition() - head->GetTransform()->GetWorldPosition();
  T_FLOAT distance_length = distance.Length();
  T_FLOAT speed = std::min(distance_length, controller->GetSpeed());
  head->Move(distance.Normalized() * speed);
}

T_INT8 BossBrain_Chase::BrainChange(T_UINT16 count, BossController* controller, BossBody* head, Player* player)
{
  TVec3f distance = player->GetTransform()->GetWorldPosition() - head->GetTransform()->GetWorldPosition();
  T_FLOAT distance_length = distance.Length();
  if (distance_length < 20.0f)
  {
    T_UINT32 rand = Util::GetRandom(0, 100);
    if (rand < 10)
    {
      return BossBrainTable::BRAIN_CHASE;
    }
    if (rand < 20)
    {
      return BossBrainTable::BRAIN_AROUND;
    }
    if (rand < 50)
    {
      return BossBrainTable::BRAIN_JUMP;
    }
  }
  return -1;
}

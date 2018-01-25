#include "BossBrain_Jump.h"
#include "BossBrainTable.h"

static const T_UINT16 JUMP_DURATION = 400;

void BossBrain_Jump::BrainInit(BossController* controller, BossBody* head, Player* player)
{
}

void BossBrain_Jump::BrainUpdate(BossController* controller, BossBody* head, Player* player)
{
  T_FLOAT d = MathConstants::PI * sinf((T_FLOAT)this->GetFrameCount() / JUMP_DURATION * MathConstants::PI);
  TVec3f move = TVec3f();
  move.y = sinf(d) * controller->GetSpeed();
  TVec3f direction = head->GetMoveDirection();
  direction.x += cosf(d) * direction.y;
  direction.z += sinf(d) * direction.y;
  direction.y = 0.0f;
  move += direction.Normalized() * cosf(d) * controller->GetSpeed();
  head->Move(move);
}

T_INT8 BossBrain_Jump::BrainChange(T_UINT16 count, BossController* controller, BossBody* head, Player* player)
{
  if (count == JUMP_DURATION)
  {
    return BossBrainTable::BRAIN_AROUND;
  }
  TVec3f distance = player->GetTransform()->GetWorldPosition() - head->GetTransform()->GetWorldPosition();
  T_FLOAT distance_length = distance.Length();
  if (distance_length > 100.0f)
  {
    return BossBrainTable::BRAIN_CHASE;
  }
  return -1;
}

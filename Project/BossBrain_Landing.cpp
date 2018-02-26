#include "BossBrain_Landing.h"
#include "BossBrainTable.h"

void BossBrain_Landing::BrainInit(BossController* controller, BossBody* head, Player* player)
{
  T_FLOAT r = Util::GetRandom(0.0f, MathConstants::PI_2);
  this->vec_ = TVec2f(cosf(r), sinf(r));
}

void BossBrain_Landing::BrainUpdate(BossController* controller, BossBody* head, Player* player)
{
  TVec3f pos = head->GetTransform()->GetPosition();
  TVec3f move = TVec3f();
  move.x = this->vec_.x;
  move.y -= 1.0f;
  move.z = this->vec_.y;
  head->GetTransform()->SetPosition(pos + move.Normalized() * controller->GetSpeed());
}

T_INT8 BossBrain_Landing::BrainChange(T_UINT16 count, BossController* controller, BossBody* head, Player* player)
{
  if (head->GetTransform()->GetWorldPosition().y < 2.0f)
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

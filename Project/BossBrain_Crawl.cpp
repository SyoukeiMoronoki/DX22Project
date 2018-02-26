#include "BossBrain_Crawl.h"
#include "BossBrainTable.h"

void BossBrain_Crawl::BrainInit(BossController* controller, BossBody* head, Player* player)
{
  this->rot_velocity_ = TVec3f(0.001f, 0.005f, 0.001f);
}

void BossBrain_Crawl::BrainUpdate(BossController* controller, BossBody* head, Player* player)
{
  head->GetTransform()->RotateY(this->rot_velocity_.y);
  head->GetTransform()->RotateX(this->rot_velocity_.x);
  head->GetTransform()->MoveZ(controller->GetSpeed());
  TVec3f pos = head->GetTransform()->GetWorldPosition();
  if (pos.y < 0.0f || pos.y > 10.0f)
  {
    this->rot_velocity_.x *= -1.0f;
  }
}

T_INT8 BossBrain_Crawl::BrainChange(T_UINT16 count, BossController* controller, BossBody* self, Player* player)
{
  if (count % 180 == 0)
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

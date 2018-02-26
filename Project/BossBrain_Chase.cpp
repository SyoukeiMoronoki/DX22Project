#include "BossBrain_Chase.h"
#include "BossBrainTable.h"
#include "BossBulletManager.h"

void BossBrain_Chase::BrainInit(BossController* controller, BossBody* head, Player* player)
{
}

void BossBrain_Chase::BrainUpdate(BossController* controller, BossBody* head, Player* player)
{
  TVec3f distance = player->GetTransform()->GetWorldPosition() - head->GetTransform()->GetWorldPosition();
  T_FLOAT distance_length = distance.Length();
  T_FLOAT speed = std::min(distance_length, controller->GetSpeed());
  head->Move(distance.Normalized() * speed);

  const T_UINT16 frame_count = this->GetFrameCount();
  const TVec3f head_pos = head->GetTransform()->GetWorldPosition();
  const TVec3f player_pos = player->GetTransform()->GetWorldPosition();
  if (frame_count % 30 == 0)
  {
    controller->GetBulletManager()->Emmision(head_pos, player_pos);
    controller->GetBulletManager()->Emmision(head_pos, player_pos + TVec3f( 1.0f, 0.0f, 1.0f));
    controller->GetBulletManager()->Emmision(head_pos, player_pos + TVec3f( 1.0f, 0.0f,-1.0f));
    controller->GetBulletManager()->Emmision(head_pos, player_pos + TVec3f(-1.0f, 0.0f, 1.0f));
    controller->GetBulletManager()->Emmision(head_pos, player_pos + TVec3f(-1.0f, 0.0f,-1.0f));
  }
  if (frame_count % 30 == 10)
  {
    controller->GetBulletManager()->Emmision(head_pos, player_pos);
  }
  if (frame_count % 30 == 20)
  {
    controller->GetBulletManager()->Emmision(head_pos, player_pos);
  }
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
      return BossBrainTable::BRAIN_CRAWL;
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

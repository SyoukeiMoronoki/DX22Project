#include "BossBrain_Around.h"
#include "BossBrainTable.h"

void BossBrain_Around::BrainInit(BossController* controller, BossBody* head, Player* player)
{
}

void BossBrain_Around::BrainUpdate(BossController* controller, BossBody* head, Player* player)
{
  Transform3D* player_transform = player->GetActor()->GetTransform();

  TVec3f head_direction = head->GetMoveDirection();
  TVec3f player_direction = player_transform->GetWorldDirection();
  T_FLOAT dot = TVec3f::InnerProduct(head_direction, player_direction);
  head->GetTransform()->LerpRotation(player->GetWorldQuaternion().Inversed(), 0.05f);
  head->GetTransform()->MoveZ(controller->GetSpeed());
}

T_INT8 BossBrain_Around::BrainChange(T_UINT16 count, BossController* controller, BossBody* head, Player* player)
{
  return -1;
}

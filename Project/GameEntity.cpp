#include "GameEntity.h"
#include "GameDirector.h"

GameEntity::GameEntity()
  : ignore_space_wall_(false)
{
}

GameEntity::~GameEntity()
{
  for (GameEntityCollider* collider : this->colliders_)
  {
    delete collider;
  }
}

void GameEntity::OnPositionChanged(GameObject* root)
{
  this->OnTransformChanged();
}

void GameEntity::OnScaleChanged(GameObject* root)
{
  this->OnTransformChanged();
}

void GameEntity::OnTransformChanged()
{
  this->is_position_changed_ = true;
}

void GameEntity::ResetTransformChangedFlag()
{
  this->is_position_changed_ = false;
}

void GameEntity::PostUpdate()
{
  if (this->ignore_space_wall_)
  {
    return;
  }
  //���E�̕ǂ��z���Ȃ��悤�ɂ��鏈��
  //���_����̋������F���̕ǂ܂ł̋����ȏ�ł����(sqrt���Ă΂�Ȃ��悤�Q�擯�m�Ŕ�r)
  const T_FLOAT world_radius = GameDirector::GetGameSetting().GetLevelParam().world_radius;
  const TVec3f current_world_pos = this->GetTransform()->GetWorldPosition();
  if (current_world_pos.LengthSquare() > world_radius * world_radius)
  {
    //�v���C���[�̋�ԏ�̈ʒu�𐳋K�����A����ɉF���̕ǂ܂ł̋�������Z���鎖�ŁA�F���̕ǃM���M���̍��W�𓾂��
    const TVec3f next_world_pos = current_world_pos.Normalized() * world_radius;
    const TVec3f current_local_pos = this->GetTransform()->GetPosition();
    this->GetTransform()->SetPosition(next_world_pos - current_world_pos + current_local_pos);
  }
}

void GameEntity::AddCollider(T_FLOAT radius)
{
  GameEntityCollider* collider = new GameEntityCollider(this);
  collider->SetRadius(radius);
  this->colliders_.push_back(collider);
}

void GameEntity::AddCollider(const TVec3f& offset, T_FLOAT radius)
{
  GameEntityCollider* collider = new GameEntityCollider(this);
  collider->SetOffset(offset);
  collider->SetRadius(radius);
  this->colliders_.push_back(collider);
}

bool GameEntity::HitCheck(GameEntity* other)
{
  std::list<GameEntityCollider*> other_colliders = other->colliders_;
  for (GameEntityCollider* a : this->colliders_)
  {
    for (GameEntityCollider* b : other_colliders)
    {
      if (a->Collision(*b))
      {
        return true;
      }
    }
    other_colliders.pop_front();
  }
  return false;
}

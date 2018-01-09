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
  //¢ŠE‚Ì•Ç‚ð‰z‚¦‚È‚¢‚æ‚¤‚É‚·‚éˆ—
  //Œ´“_‚©‚ç‚Ì‹——£‚ª‰F’ˆ‚Ì•Ç‚Ü‚Å‚Ì‹——£ˆÈã‚Å‚ ‚ê‚Î(sqrt‚ªŒÄ‚Î‚ê‚È‚¢‚æ‚¤‚Qæ“¯Žm‚Å”äŠr)
  const T_FLOAT world_radius = GameDirector::GetGameSetting().GetLevelParam().world_radius;
  const TVec3f current_world_pos = this->GetTransform()->GetWorldPosition();
  if (current_world_pos.LengthSquare() > world_radius * world_radius)
  {
    //ƒvƒŒƒCƒ„[‚Ì‹óŠÔã‚ÌˆÊ’u‚ð³‹K‰»‚µA‚»‚ê‚É‰F’ˆ‚Ì•Ç‚Ü‚Å‚Ì‹——£‚ðæŽZ‚·‚éŽ–‚ÅA‰F’ˆ‚Ì•ÇƒMƒŠƒMƒŠ‚ÌÀ•W‚ð“¾‚ê‚é
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

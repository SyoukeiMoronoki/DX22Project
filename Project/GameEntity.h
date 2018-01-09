#pragma once

#include <list>
#include <HalEngine.h>

#include "GameEntityCollider.h"

class GameEntity : public GameObject3D
{
public:
  GameEntity();
  virtual ~GameEntity();

public:
  virtual void OnPositionChanged(GameObject* root) override;
  virtual void OnScaleChanged(GameObject* root) override;
  virtual void OnTransformChanged();

  void ResetTransformChangedFlag();

public:
  void PostUpdate() override;

public:
  void AddCollider(T_FLOAT radius);
  void AddCollider(const TVec3f& offset, T_FLOAT radius);
  bool HitCheck(GameEntity* other);

public:
  inline void SetIgnoreSpaceWall(bool ignore)
  {
    this->ignore_space_wall_ = ignore;
  }
  inline bool IsIgnoreSpaceWall() const
  {
    return this->ignore_space_wall_;
  }

private:
  std::list<GameEntityCollider*> colliders_;
  bool is_position_changed_;
  bool ignore_space_wall_;
};
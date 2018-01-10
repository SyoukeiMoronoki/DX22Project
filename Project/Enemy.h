#pragma once

#include "../Engine/AnimatedSprite.h"
#include "GameEntity.h"
#include "EnemyData.h"

class Enemy : public GameEntity
{
public:
  enum EnemySubspecies
  {
    ENEMY_SUB_NORMAL,
    ENEMY_SUB_RED,
    ENEMY_SUB_GREEN,
    ENEMY_SUB_BLUE,

    ENEMY_SUB_DATANUM,
  };

public:
  Enemy();
  ~Enemy();

public:
  virtual void OnAllocated();
  virtual void OnFree();

  virtual void Update() override;
  virtual void OnDamaged();
  virtual void OnWeakPointDamaged();

  void AddMoveDelay(T_UINT8 delay);
  void SetMoveDelayNegative(T_UINT8 delay);

  void MoveRadialRate(T_FLOAT rate);
  void MoveTangential(T_FLOAT value);

  void SetWeakPoint(const TVec3f& pos);
  bool WeakPointHitCheck(Collider3D* collider);

public:
  void Spawn(const EnemyData* data);

public:
  T_UINT16 GetCount() const
  {
    return this->count_;
  }

  inline bool IsAlive() const
  {
    return true;
  }
  
private:
  bool is_allocated_;

  T_UINT16 count_;
  T_UINT8 move_delay_;

  T_UINT8 damage_effect_count_;

  T_UINT8 death_count_;

  Collider3D_Sphare* weak_point_;
  BillBoard* weak_point_sprite_;

  const EnemyData* data_;
  TiledTextureRegion* texture_region_;
  AnimatedSprite3D* sprite_;
  BillBoard* body_;
};
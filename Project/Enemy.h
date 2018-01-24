#pragma once

#include "../Engine/AnimatedSprite.h"
#include "GameEntity.h"
#include "EnemyData.h"
#include "EnemyBulletManager.h"

class Player;

class Enemy : public GameEntity, public IPoolAllocatable
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

  enum SpecialSpotColor
  {
    SPOT_RED,
  };

public:
  Enemy();
  ~Enemy();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

  virtual void EnemyUpdate(Player* player);
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
  inline void SetEnemyBulletManager(EnemyBulletManager* manager)
  {
    this->bullet_manager_ = manager;
  }

  inline T_FLOAT GetRadius() const
  {
    return this->body_->GetTransform()->GetScaleMax() * 0.5f;
  }

  inline T_UINT16 GetCount() const
  {
    return this->count_;
  }

  inline bool IsAlive() const
  {
    return !this->is_dead_;
  }
 
  inline void SetHomingPos(T_FLOAT rad, T_FLOAT radius)
  {
    this->homing_rad_ = rad;
    this->homing_radius_ = radius;
  }

private:
  EnemyBulletManager* bullet_manager_;
  T_FLOAT homing_rad_;
  T_FLOAT homing_radius_;

  T_UINT16 count_;
  T_UINT8 move_delay_;

  T_UINT8 damage_effect_count_;

  T_UINT8 death_count_;

  T_UINT8 bullet_emmision_delay_;

  Collider3D_Sphare* weak_point_;
  Sprite3D* weak_point_sprite_;

  const EnemyData* data_;
  TiledTextureRegion* texture_region_;
  AnimatedSprite3D* body_;
  bool is_dead_;
};
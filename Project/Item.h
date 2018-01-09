#pragma once

#include <HalEngine.h>

#include "GameEntity.h"
#include "Player.h"
#include "ItemData.h"

class Item : public GameEntity, public IPoolAllocatable
{
public:
  Item();
  ~Item() {}

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

  virtual void Update() override;

public:
  void OnHitToPlayer(Player* player);
  void AddForce(T_FLOAT unit_x, T_FLOAT unit_y);
  void AddEmissionForce(T_FLOAT unit_x, T_FLOAT unit_y);

  void Gravitate(GameEntity* entity);

public:
  void Spawn(const ItemData* data);

private:
  const ItemData* data_;
  T_UINT16 life_time_;

  TVec3f velocity_;
  T_FLOAT friction_;
};

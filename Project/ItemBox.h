#pragma once

#include <HalEngine.h>

#include "ItemBoxContents.h"
#include "GameEntity.h"

class Player;

class ItemBox : public GameEntity, public IPoolAllocatable
{
public:
  ItemBox();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

  virtual void Update() override;

public:
  void Spawn(T_UINT16 life_time_, T_UINT16 hp, const ItemBoxContents* contents);
  void OnHitToPlayer(Player* player);

private:
  void OnHpChanged();

public:
  inline bool IsAlive() const
  {
    return this->now_hp_ > 0;
  }

private:
  T_UINT16 max_hp_;
  T_UINT16 now_hp_;

  T_FLOAT life_time_;

  const ItemBoxContents* contents_;
};

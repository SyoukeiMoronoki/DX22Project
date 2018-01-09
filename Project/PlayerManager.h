#pragma once

#include <vector>
#include <HalEngine.h>
#include "GameEntityManager.h"
#include "Player.h"
#include "AttackManager.h"

class CollisionHelper;

class PlayerManager : public GameEntityManager<Player>
{
public:
  PlayerManager(const std::vector<PlayerEntry*>& entries);
  virtual ~PlayerManager();

public:
  virtual void Loop(std::function<void(Player*)> func) override;
  virtual void LoopIncludingPool(std::function<void(Player*)> func) override;
  virtual Player* Select(std::function<bool(Player*)> condition) override;
  virtual void SelectAll(std::deque<Player*>* dest, std::function<bool(Player*)> condition) override;

public:
  //void ApplyUI(UI_Player* ui);
  void AttachAdditionToField();
  void DetachAdditionFromField();

  void Collision(CollisionHelper* helper);

protected:
  AttackManager* GetAttackManager(Player* player);
  
private:
  std::vector<Player*> players_;

};

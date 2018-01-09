#pragma once

#include <deque>
#include <map>
#include <HalEngine.h>
#include "Attack.h"
#include "GameEntity.h"
#include "GameEntityManager.h"

class AttackManager
{
public:
  AttackManager(T_UINT16 attack_count_);
  ~AttackManager();

public:
  void Update();
  void Spawn(const AttackData* data, AttackFacade_Attach* facade);

  Attack* GetHitAttack(GameEntity* entity);
  void GetHitAttacks(GameEntity* entity, std::deque<Attack*>* dest);
  template<class T>
  void GetHitAttacks(GameEntityManager<T>* entity_manager, std::map<T*, std::deque<Attack*>>* dest)
  {
    dest->clear();
    for (std::list<T*>::iterator itr = entity_manager->begin(); itr != entity_manager->end(); ++itr)
    {
      this->GetHitAttacks((*itr), &((*dest)[(*itr)]));
    }
  }

  void AttachToField(GameObject3D* entity);
  void DetachFromField();

private:
  Attack* GetReadyAttack() const;

private:
  Attack** attacks_;
  T_UINT16 attack_count_;
};
#pragma once

#include <map>
#include <list>
#include <deque>
#include <HalEngine.h>
#include "GameEntity.h"

template<class T>
class GameEntityManager
{
public:
  virtual void Loop(std::function<void(T*)> func) = 0;
  virtual void LoopIncludingPool(std::function<void(T*)> func) = 0;
  virtual T* Select(std::function<bool(T*)> condition) = 0;
  virtual void SelectAll(std::deque<T*>* dest, std::function<bool(T*)> condition) = 0;

protected:
  virtual bool OnManagedEntityUpdate(T* entity) { return true; }

public:
  void AttachToEntity(GameObject3D* entity)
  {
    this->LoopIncludingPool([&](T* p) {
      entity->AddChild(p);
    });
  }

  void DetachFromEntity()
  {
    this->Loop([&](T* p) {
      p->RemoveSelf();
    });
  }

  T* GetHitEntity(GameEntity* other)
  {
    return Select([&](T* p) {
      return p->HitCheck(other);
    });
  }

  template<class T2>
  T* GetHitEntity(GameEntityManager<T2>* other_collider_manager, T2** other_dest)
  {
    return Select([&](T* p) {
      (*other_dest) = other_collider_manager->GetHitEntity((*itr));
      return (*other_dest);
    });
  }

  void GetHitEntities(GameEntity* other, typename std::deque<T*>* dest)
  {
    return SelectAll(
      dest,
      [&](T* p) {
        return p->HitCheck(other);
      }
    );
  }

  template<class T2>
  void GetHitEntities(GameEntityManager<T2>* other_collider_manager, typename std::map<T*, std::deque<T2*>>* dest)
  {
    this->Loop([&](T* p)
    {
      other_collider_manager->GetHitEntities(p, &((*dest)[p]));
    });
  }

};

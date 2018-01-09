#pragma once

#include <HalEngine.h>
#include "GameEntityManager.h"

template<class T>
class AllocatableGameEntityManager : public GameEntityManager<T>
{
public:
  AllocatableGameEntityManager(T_UINT16 size)
    : allocator_(size)
  {
    this->Loop([](T* p) {
      p->SetVisible(false);
    });
  }

  virtual ~AllocatableGameEntityManager()
  {
    this->Loop([](T* p) {
      p->RemoveSelf();
    });
  }

public:
  virtual void Loop(std::function<void(T*)> func) override
  {
    for (std::list<T*>::iterator itr = this->allocator_.begin(); itr != this->allocator_.end(); ++itr)
    {
      func((*itr));
    }
  }

  virtual void LoopIncludingPool(std::function<void(T*)> func) override
  {
    for (std::deque<T*>::iterator itr = this->allocator_.PoolBegin(); itr != this->allocator_.PoolEnd(); ++itr)
    {
      func((*itr));
    }
    for (std::list<T*>::iterator itr = this->allocator_.begin(); itr != this->allocator_.end(); ++itr)
    {
      func((*itr));
    }
  }

  virtual T* Select(std::function<bool(T*)> condition) override
  {
    for (std::list<T*>::iterator itr = this->allocator_.begin(); itr != this->allocator_.end(); ++itr)
    {
      if (condition((*itr)))
      {
        return (*itr);
      }
    }
    return nullptr;
  }

  virtual void SelectAll(std::deque<T*>* dest, std::function<bool(T*)> condition) override
  {
    for (std::list<T*>::iterator itr = this->allocator_.begin(); itr != this->allocator_.end(); ++itr)
    {
      if (condition((*itr)))
      {
        dest->push_back((*itr));
      }
    }
  }

public:
  inline T* Allocate()
  {
    return this->allocator_.Allocate();
  }
  inline void Free(T* p)
  {
    return this->allocator_.Free(p);
  }

private:
  PoolAllocator<T> allocator_;

};
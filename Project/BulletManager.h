#pragma once

#include <HalEngine.h>

#include "AllocatableGameEntityManager.h"
#include "Bullet.h"

class BulletManager : public AllocatableGameEntityManager<Bullet>
{
public:
  BulletManager(T_UINT16 count);

public:
  void Update();

public:
  void Emmision(GameObject3D* emmitter);

};
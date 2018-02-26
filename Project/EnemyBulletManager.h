#pragma once

#include <HalEngine.h>

#include "AllocatableGameEntityManager.h"
#include "EnemyBullet.h"

class EnemyBulletManager : public AllocatableGameEntityManager<EnemyBullet>
{
public:
  EnemyBulletManager(T_UINT16 count);

public:
  void Update();

public:
  void Emmision(GameObject3D* emmitter, GameObject3D* target);

};
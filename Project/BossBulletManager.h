#pragma once
#include <HalEngine.h>

#include "AllocatableGameEntityManager.h"
#include "BossBullet.h"

class BossBulletManager : public AllocatableGameEntityManager<BossBullet>
{
public:
  BossBulletManager(T_UINT16 count);

public:
  void Update();

public:
  void Emmision(GameObject3D* emmitter, GameObject3D* target);

};
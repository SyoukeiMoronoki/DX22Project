#pragma once

#include <HalEngine.h>
#include "Player.h"
#include "BossBody.h"
#include "BossController.h"

class BossBrain
{
public:
  BossBrain();
  ~BossBrain() {}

public:
  void Init(BossController* controller, BossBody* head, Player* player);
  void Update(BossController* controller, BossBody* head, Player* player);

protected:
  virtual void BrainInit(BossController* controller, BossBody* head, Player* player) = 0;
  virtual void BrainUpdate(BossController* controller, BossBody* head, Player* player) = 0;
  virtual T_INT8 BrainChange(T_UINT16 count, BossController* controller, BossBody* head, Player* player) = 0;

protected:
  inline T_UINT16 GetFrameCount() const
  {
    return this->count_;
  }

private:
  T_UINT16 count_;
  
};
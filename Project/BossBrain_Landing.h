#pragma once

#include "BossBrain.h"

class BossBrain_Landing : public BossBrain
{
protected:
  virtual void BrainInit(BossController* controller, BossBody* head, Player* player) override;
  virtual void BrainUpdate(BossController* controller, BossBody* self, Player* player) override;

  virtual T_INT8 BrainChange(T_UINT16 count, BossController* controller, BossBody* self, Player* player) override;

private:
  TVec2f vec_;
};
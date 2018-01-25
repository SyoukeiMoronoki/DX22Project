#pragma once

#include <HalEngine.h>

#include "Field.h"
#include "BossController.h"
#include "GameConstants.h"

class GameSceneDirector
{
public:
  static GameSceneDirector& GetInstance()
  {
    static GameSceneDirector self;
    return self;
  }

private:
  GameSceneDirector()
    : score_(0)
    , bonus_(0)
  {}

public:
  inline void Init(Field* field, Player* player, BossController* boss)
  {
    this->field_ = field;
    this->player_ = player;
    this->boss_ = boss;

    this->score_ = 0;
    this->bonus_ = 0;
    this->current_phase_ = GameConstants::PHASE_START;
    this->time_count_ = GameConstants::GetPhaseTime(this->current_phase_);
  }

  bool Update()
  {
    if (this->current_phase_ == GameConstants::PHASE_DATANUM)
    {
      return false;
    }
    this->time_count_--;
    if (this->IsGameOver())
    {
      this->time_count_ -= 100;
    }
    if (this->time_count_ <= 0)
    {
      this->current_phase_++;
      if (this->current_phase_ == GameConstants::PHASE_DATANUM)
      {
        return false;
      }
      this->time_count_ = GameConstants::GetPhaseTime(this->current_phase_);
    }
    return true;
  }

  inline T_UINT32 GetTimeCount() const
  {
    return this->time_count_;
  }

  inline void AddScore(T_UINT32 score)
  {
    this->score_ += score;
  }

  inline T_UINT32 GetScore()
  {
    return this->score_;
  }

  inline void AddBonus(T_UINT32 bonus)
  {
    this->bonus_ += bonus;
  }

  inline T_UINT32 GetBonus()
  {
    return this->bonus_;
  }

  inline const Field* GetField() const
  {
    return this->field_;
  }
  
  inline const BossController* GetBoss() const
  {
    return this->boss_;
  }

  inline bool IsGameOver() const
  {
    return this->player_->GetHP() == 0;
  }

  inline T_FLOAT GetTimeProgress() const
  {
    return 1.0f - (T_FLOAT)this->time_count_ / GameConstants::GetPhaseTime(this->current_phase_);
  }

  inline T_UINT8 GetCurrentPhase() const
  {
    return this->current_phase_;
  }

private:
  Player* player_;
  Field* field_;
  BossController* boss_;

  T_UINT32 score_;
  T_UINT32 bonus_;
  T_INT32 time_count_;
  T_UINT8 current_phase_;
};

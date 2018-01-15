#pragma once

#include <HalEngine.h>

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
  inline void Init()
  {
    this->score_ = 0;
    this->bonus_ = 0;
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

private:
  T_UINT32 score_;
  T_UINT32 bonus_;
};
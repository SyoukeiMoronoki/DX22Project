#pragma once

#include <HalEngine.h>

#include "NumberView.h"
#include "Gauge.h"

class UI_Player : public GameObject2D
{
public:
  UI_Player();
  ~UI_Player();

public:
  void GameInit();
  void Update();

public:
  inline NumberView* GetTimeView() const
  {
    return this->time_view_;
  }
  inline NumberView* GetScoreView() const
  {
    return this->score_view_;
  }
  inline Gauge* GetHPView() const
  {
    return this->hp_gauge_;
  }
  inline Gauge* GetEarView() const
  {
    return this->ear_gauge_;
  }

public:
  NumberView* time_view_;
  NumberView* score_view_;
  Gauge* hp_gauge_;
  Gauge* ear_gauge_;

};

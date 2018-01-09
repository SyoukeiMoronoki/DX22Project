#pragma once

#include "AllocatableGameEntityManager.h"
#include "Star.h"

class StarManager : public AllocatableGameEntityManager<Star>
{
public:
  struct LevelParam
  {
    LevelParam(T_UINT16 star_count)
      : star_count(star_count)
      , star_spawn_delay(1)
      , star_scale_min(0.0f)
      , star_scale_max(1.0f)
      , star_lifetime(0)
      , star_spawn_radius(0.0f)
    {}

    T_UINT16 star_count;
    T_UINT16 star_spawn_delay;
    T_FLOAT star_scale_min;
    T_FLOAT star_scale_max;
    T_UINT16 star_lifetime;
    T_FLOAT star_spawn_radius;
  };

public:
  StarManager(const LevelParam& level_param);

public:
  void Update();

private:
  const LevelParam level_param_;
  T_INT16 count_;
};
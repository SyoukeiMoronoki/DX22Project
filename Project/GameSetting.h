#pragma once

#include <vector>
#include <HalEngine.h>

struct GameLevelParam
{
  //初期値のままの要素があるとエラーが出力されるように
  GameLevelParam()
    : world_radius(0.0f)
    , gacha_star_count(0)
    , gacha_star_spawn_delay(0)
    , gacha_star_lifetime(0)
    , accel_weight(0.0f)
    , speed_weight(0.0f)
    , rot_speed_weight(0.0f)
    , power_weight(0.0f)
  {}

  //原点から宇宙の壁までの距離
  T_FLOAT world_radius;
  
  T_UINT16 gacha_star_count;
  T_UINT16 gacha_star_spawn_delay;
  T_UINT16 gacha_star_lifetime;

  //乗り物のステータスにかかる重み
  T_FLOAT accel_weight;
  T_FLOAT speed_weight;
  T_FLOAT rot_speed_weight;
  T_FLOAT power_weight;
};

class GameSetting
{
public:
  GameSetting();
  ~GameSetting();

public:
  inline const GameLevelParam& GetLevelParam() const
  {
    return this->level_param_;
  }
  inline GameLevelParam& GetLevelParam()
  {
    return this->level_param_;
  }

private:
  GameLevelParam level_param_;

};
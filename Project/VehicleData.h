#pragma once

#include <string>
#include <HalEngine.h>

struct VehicleData
{
  T_UINT8 id;
  std::string name;
  std::string comment;
  T_UINT16 accel;
  T_UINT16 speed;
  T_UINT16 rot_speed;
  T_UINT16 power;
  T_FLOAT radius;
};


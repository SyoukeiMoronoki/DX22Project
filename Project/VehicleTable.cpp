#include "VehicleTable.h"

namespace VehicleTable
{

static const VehicleData ERROR = {T_UINT8_MAX, "エラー", "このメッセージが みれるのは おかしいよ"};

static const VehicleData VEHICLE_DATAS[VEHICLE_ID_DATANUM] =
{
  //id,               name,     com,     accel, speed, rot_speed, power radius, 
  { VEHICLE_ID_NONE,  "裸",       "",    100,   100,   100,       100,  32.0f },
  { VEHICLE_ID_CAR,   "車",       "",    100,   100,   100,       100,  64.0f },
};

const VehicleData& GetVehicleData(T_UINT8 id)
{
  for (T_UINT8 i = 0; i < VEHICLE_ID_DATANUM; ++i)
  {
    if (VEHICLE_DATAS[i].id == id)
    {
      return VEHICLE_DATAS[i];
    }
  }
  return ERROR;
}

}
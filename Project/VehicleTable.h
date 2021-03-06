#pragma once

#include "Vehicle.h"

namespace VehicleTable
{

//一番目のID(=0)は初期状態での乗り物となる
enum VehicleID
{
  VEHICLE_ID_NONE,
  VEHICLE_ID_CAR,

  VEHICLE_ID_DATANUM,
};

const VehicleData& GetVehicleData(T_UINT8 id);

}
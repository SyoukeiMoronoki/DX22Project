#pragma once

#include "Vehicle.h"

namespace VehicleTable
{

//��Ԗڂ�ID(=0)�͏�����Ԃł̏�蕨�ƂȂ�
enum VehicleID
{
  VEHICLE_ID_NONE,
  VEHICLE_ID_CAR,

  VEHICLE_ID_DATANUM,
};

const VehicleData& GetVehicleData(T_UINT8 id);

}
#pragma once

#include "Vehicle.h"

namespace VehicleTable
{

//ˆê”Ô–Ú‚ÌID(=0)‚Í‰Šúó‘Ô‚Å‚Ìæ‚è•¨‚Æ‚È‚é
enum VehicleID
{
  VEHICLE_ID_NONE,
  VEHICLE_ID_CAR,

  VEHICLE_ID_DATANUM,
};

const VehicleData& GetVehicleData(T_UINT8 id);

}
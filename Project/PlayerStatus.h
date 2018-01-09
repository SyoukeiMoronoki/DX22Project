#pragma once

#include "AnimalData.h"
#include "VehicleData.h"

class PlayerStatus
{
public:
  PlayerStatus(const AnimalData& animal_data, T_UINT8 handicap);
  ~PlayerStatus();

public:
  void ChangeVehicle(const VehicleData& vehicle);

private:
  void OnChangeVehicle();

public:
  inline const AnimalData& GetAnimalData()
  {
    return this->animal_data_;
  }
  inline const VehicleData& GetVehcileData()
  {
    return *this->vehicle_data_;
  }
  inline T_FLOAT GetAccel() const
  {
    return this->accel_;
  }
  inline T_FLOAT GetMaxSpeed() const
  {
    return this->max_speed_;
  }
  inline T_FLOAT GetRotationSpeed() const
  {
    return this->rot_speed_;
  }
  inline T_FLOAT GetPower() const
  {
    return this->power_;
  }

private:
  const AnimalData& animal_data_;
  const T_UINT8 handicap_;

  const VehicleData* vehicle_data_;

  T_FLOAT accel_;
  T_FLOAT max_speed_;
  T_FLOAT rot_speed_;
  T_FLOAT power_;

};
#include "PlayerStatus.h"
#include "VehicleTable.h"
#include "GameDirector.h"

PlayerStatus::PlayerStatus(const AnimalData& animal_data, T_UINT8 handicap)
  : animal_data_(animal_data)
  , handicap_(handicap)
  , vehicle_data_(&VehicleTable::GetVehicleData(0))
{
  //TODO: Handicap‚Ì“K—pˆ—
  this->OnChangeVehicle();
}

PlayerStatus::~PlayerStatus()
{
}

void PlayerStatus::ChangeVehicle(const VehicleData& vehicle)
{
  this->vehicle_data_ = &vehicle;
  this->OnChangeVehicle();
}

void PlayerStatus::OnChangeVehicle()
{
  const GameLevelParam& param = GameDirector::GetGameSetting().GetLevelParam();
  this->accel_ = this->vehicle_data_->accel * param.accel_weight;
  this->max_speed_ = this->vehicle_data_->speed * param.speed_weight;
  this->rot_speed_ = this->vehicle_data_->rot_speed * param.rot_speed_weight;
  this->power_ = this->vehicle_data_->power * param.power_weight;
}

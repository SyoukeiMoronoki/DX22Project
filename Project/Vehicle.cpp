#include "Vehicle.h"

#include "Player.h"

Vehicle::Vehicle(Player* player, const VehicleData* data)
  : player_(player)
  , data_(data)
  , card_manager_()
{
}

Vehicle::~Vehicle()
{
}


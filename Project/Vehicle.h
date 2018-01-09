#pragma once

#include <deque>
#include <HalEngine.h>

#include "GameEntityCollider.h"

#include "Player.h"
#include "VehicleData.h"
#include "CardManager.h"

class VehicleAttribute;

class Vehicle : public GameObject2D
{
public:
  Vehicle(Player* player, const VehicleData* data);
  ~Vehicle();
  
public:
  virtual T_FLOAT GetHitRadius() const = 0;
  virtual bool Update(const UpdateEventState& state) = 0;
  virtual void OnMove(T_FLOAT length) = 0;
  virtual void OnEnergyUpdate(T_FLOAT energy) = 0;
  virtual void OnEnergyLevelUp(T_FLOAT energy) = 0;
  virtual void OnHealFromTrap() = 0;
  virtual void OnDamageFromTrap() = 0;

  virtual void GetIn(Vehicle* old) = 0;
  virtual void GetOut(Vehicle* next) = 0;

public:
  inline const VehicleData* GetData() const
  {
    return this->data_;
  }
  inline CardManager* GetCardManager()
  {
    return &this->card_manager_;
  }

protected:
  Player* player_;
  CardManager card_manager_;

private:
  const VehicleData* data_;
};


#pragma once

#include <HalEngine.h>

class Spot : public Sprite3D
{
public:
  enum SpotType
  {
    SPOT_WEAK_POINT,
    SPOT_GUARD_POINT,
  };
  
public:
  Spot();

public:


private:
  SpotType type_;

};
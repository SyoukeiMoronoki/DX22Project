#pragma once

#include <HalEngine.h>

class Field : public GameObject3D
{
public:
  enum Direction
  {
    DIRECTION_SOUTH,
    DIRECTION_WEAST,
    DIRECTION_NORTH,
    DIRECTION_EAST,

    DIRECTION_DATANUM,
  };

public:
  Field();
  ~Field();

public:
  void Update() override;

private:
  Material* sky_material_;
  Plane3D* skys_[DIRECTION_DATANUM];
  Plane3D* zenith_;
  Plane3D* ground_;

};
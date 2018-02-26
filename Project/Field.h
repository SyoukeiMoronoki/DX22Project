#pragma once

#include <HalEngine.h>
#include "Player.h"

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
  void Update(Player* player);

public:
  inline T_FLOAT GetLightBrightness() const
  {
    return this->light_brightness_;
  }

  inline const TVec3f& GetLightPosition() const
  {
    return this->light_position_;
  }

  inline const TVec3f& GetLightDirection() const
  {
    return this->light_direction_;
  }

  inline const Color4F& GetLightDiffuse() const
  {
    return this->light_diffuse_;
  }

  inline const Color4F& GetFieldAmbientColor() const
  {
    return this->field_light_color_;
  }

private:
  Material* sky_material_;
  Plane3D* skys_[DIRECTION_DATANUM];
  Plane3D* zenith_;
  Plane3D* ground_;

  T_UINT16 shot_effect_duration_;
  
  T_FLOAT light_brightness_;
  TVec3f light_position_;
  TVec3f light_direction_;
  Color4F light_diffuse_;

  Color4F field_ambient_color_;
  Color4F field_fade_color_;
  Color4F field_light_color_;

};
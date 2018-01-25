#pragma once

#include <HalEngine.h>

class PlayerActor : public GameObject3D
{
public:
  PlayerActor(GameObject3D* player);
  ~PlayerActor();

public:
  void Update() override;

public:
  void Walk(T_FLOAT x, T_FLOAT y);
  void Face(const Quaternion& direction_quaternion);
  
public:
  inline const Quaternion& GetDirectionQuaternion() const
  {
    return this->direction_quaternion_;
  }

private:
  GameObject3D* const player_;
  Cube3D* body_;
  Cube3D* gun_;
  Quaternion direction_quaternion_;

};
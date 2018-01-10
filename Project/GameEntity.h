#pragma once

#include <HalEngine.h>

#include "GameEntityCollider.h"

#include "NumberView.h"

class GameEntity : public GameObject3D
{
public:
  GameEntity();
  virtual ~GameEntity();

public:
  virtual void OnAllocated();
  virtual void OnFree();

public:
  void SetRadialRates(T_FLOAT radial_rate, T_FLOAT tangential_rate);
  //���a��̈ړ�
  virtual void MoveRadialRate(T_FLOAT rate);
  //�~����̈ړ��A�l�ɑ΂��Ĕ��a��̈ʒu����ړ������v�Z����
  virtual void MoveTangential(T_FLOAT value);

public:
  void AddCollider(GameEntityCollider* collider);
  bool HitCheck(Collider3D* collider);

public:
  void SetEnabled(bool enabled)
  {
    this->is_enabled_ = enabled;
  }
  bool IsEnabled()
  {
    return this->is_enabled_;
  }
  T_FLOAT GetRadialRate()
  {
    return this->radial_rate_;
  }

private:
  bool is_enabled_;

  GameEntityCollider** collider_;
  T_UINT8 collider_count_;

  T_FLOAT radial_rate_; //���a��̈ʒu
  T_FLOAT tangential_rate_; //�~����̈ʒu
  T_FLOAT tangential_move_; //�~����̈ړ���
};
#pragma once

#include <HalEngine.h>

class NumberView : public GameObject2D
{
public:
  NumberView(T_UINT8 digit_count, T_FLOAT width);
  ~NumberView();

public:
  void ViewInit(T_UINT32 value);
  void Update();

public:
  void SetValue(T_UINT32 value);
  void AnimationFinish();

private:
  void OnUpdateView();

public:
  inline const T_UINT32 GetValue() const
  {
    return (T_UINT32)this->value_;
  }
  inline bool IsAnimated() const
  {
    return this->value_ != this->display_value_;
  }
  inline void SetDuration(T_UINT16 duration)
  {
    this->duration_ = duration;
  }

private:
  const T_UINT8 digit_count_;
  T_FLOAT display_value_;
  T_FLOAT value_;
  T_FLOAT count_value_;
  T_UINT16 duration_;
  AnimatedSprite** sprites_;
};
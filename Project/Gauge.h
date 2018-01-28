#pragma once

#include <HalEngine.h>

class Gauge : public GameObject2D
{
public:
  Gauge(const Texture* texture, T_FLOAT width, T_FLOAT height);
  ~Gauge();

public:
  void ViewInit(T_UINT32 max_value, T_UINT32 value);
  void Update();

public:
  void SetMaxValue(T_UINT32 max_value);
  void SetValue(T_UINT32 value);
  void OnUpdateView();

private:
  T_FLOAT width_;
  Sprite* sprite_;
  T_UINT32 value_;
  T_UINT32 display_value_;
  T_UINT32 value_max_;
};


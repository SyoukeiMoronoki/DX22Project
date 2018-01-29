#include "Gauge.h"
#include <algorithm>

static const T_FLOAT DISPLAY_COUNT_UPDATE_RATE = 0.8f;

Gauge::Gauge(const Texture& texture, T_FLOAT width, T_FLOAT height)
{
  this->width_ = width;
  this->sprite_ = Sprite::CreateWithTexture(texture);
  this->sprite_->GetTransform()->SetScaleX((T_FLOAT)width / this->sprite_->GetWidth());
  this->sprite_->GetTransform()->SetScaleY((T_FLOAT)height / this->sprite_->GetHeight());
  this->sprite_->GetTransform()->SetX(width * 0.5f);
  this->AddChild(this->sprite_);
}

Gauge::~Gauge()
{
  delete this->sprite_;
}

void Gauge::ViewInit(T_UINT32 max_value, T_UINT32 value)
{
  this->value_max_ = max_value;
  this->value_ = value;
  this->display_value_ = value;
  this->OnUpdateView();
}

void Gauge::Update()
{
  if (this->value_ == this->display_value_)
  {
    return;
  }
  T_FLOAT value_sub = (T_FLOAT)this->value_ - (T_FLOAT)this->display_value_;
  T_FLOAT move_value = value_sub * DISPLAY_COUNT_UPDATE_RATE;
  if (fabs(move_value) < 1.0f)
  {
    this->display_value_ = this->value_;
  }
  else
  {
    this->display_value_ += (T_UINT32)move_value;
  }
  this->OnUpdateView();
}

void Gauge::SetMaxValue(T_UINT32 max_value)
{
  this->value_max_ = max_value;
  this->display_value_ = std::min(max_value, this->display_value_);
  this->value_ = std::min(max_value, this->value_);
  this->OnUpdateView();
}

void Gauge::SetValue(T_UINT32 value)
{
  this->value_ = value;
}

void Gauge::OnUpdateView()
{
  const T_FLOAT scale_x = this->width_ / this->sprite_->GetWidth();
  const T_FLOAT rate = (T_FLOAT)this->display_value_ / this->value_max_;
  this->sprite_->GetTransform()->SetScaleX(scale_x * rate);
  this->sprite_->GetTransform()->SetX(this->width_ * 0.5f * rate);
}


#include "NumberView.h"
#include "../Engine/Director.h"

#include "Asset.h"

NumberView::NumberView(T_UINT8 digit_count, T_FLOAT width)
  : digit_count_(digit_count)
  , display_value_(0.0f)
  , value_(0.0f)
  , count_value_(0.0f)
  , duration_(1)
{
  this->sprites_ = new AnimatedSprite*[digit_count];
  const T_FLOAT digit_width = width / digit_count;
  const T_FLOAT offset_x = -digit_width * 0.5f;
  //”Ô†‚ªá‚¢‡‚©‚ç‚P‚ÌˆÊ‚ğ’S“–
  for (T_UINT8 i = 0; i < digit_count; ++i)
  {
    this->sprites_[i] = AnimatedSprite::CreateWithTexture(&Asset::Texture::FONT_NUMBER, 5, 2);
    this->sprites_[i]->GetTiledTextureRegion()->SetXNum(5);
    this->sprites_[i]->GetTiledTextureRegion()->SetYNum(2);
    this->sprites_[i]->GetTiledTextureRegion()->FitToTexture();
    this->sprites_[i]->FitToTexture();
    //this->sprites_[i]->SetAnimateRange(0, 9);
    this->sprites_[i]->GetTransform()->SetScale(digit_width / this->sprites_[i]->GetWidth());
    this->sprites_[i]->GetTransform()->SetX(offset_x + width - digit_width * i);
    this->AddChild(this->sprites_[i]);
  }
}

NumberView::~NumberView()
{
}

void NumberView::ViewInit(T_UINT32 value)
{
  this->value_ = (T_FLOAT)value;
  this->display_value_ = (T_FLOAT)value;
  this->OnUpdateView();
}

void NumberView::Update()
{
  if (this->value_ == this->display_value_)
  {
    return;
  }
  this->display_value_ += this->count_value_;
  if (fabs(this->value_ - this->display_value_) < 1.0f)
  {
    this->display_value_ = this->value_;
  }
  this->OnUpdateView();
}

void NumberView::SetValue(T_UINT32 value)
{
  this->value_ = (T_FLOAT)value;
  this->count_value_ = (this->value_ - this->display_value_) / (T_FLOAT)this->duration_;
}

void NumberView::AnimationFinish()
{
  this->display_value_ = this->value_;
  this->OnUpdateView();
}

void NumberView::OnUpdateView()
{
  T_UINT32 num = (T_UINT32)this->display_value_;
  T_UINT8 digit_index = 0;
  while (num != 0)
  {
    this->sprites_[digit_index]->SetCurrentIndex(num % 10);
    num /= 10;
    digit_index++;
  }
  for (T_UINT8 i = digit_index; i < this->digit_count_; ++i)
  {
    this->sprites_[i]->SetCurrentIndex(0);
  }
}



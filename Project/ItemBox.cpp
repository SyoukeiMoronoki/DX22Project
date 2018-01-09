#include "ItemBox.h"
#include <algorithm>

#include "Player.h"

static const T_UINT8 BOX_TEXTURE_X_NUM = 4;
static const T_UINT8 BOX_TEXTURE_Y_NUM = 4;

static const T_FLOAT BOX_RADIUS = 32.0f;
static const T_UINT16 BOX_ALERT_LIFETIME = 180;
static const T_UINT16 BOX_ALERT_GRACE = 300;

ItemBox::ItemBox()
  : max_hp_(0)
  , now_hp_(0)
  , life_time_(0)
{
}

void ItemBox::OnAllocated()
{
}

void ItemBox::OnFree()
{
  this->SetVisible(false);
}

void ItemBox::Update()
{
  this->life_time_ -= HalEngine::Time::DeltaTime();
  if (this->life_time_ < BOX_ALERT_LIFETIME)
  {
    this->SetVisible(!this->IsVisible());
  }
}

void ItemBox::Spawn(T_UINT16 life_time, T_UINT16 hp, const ItemBoxContents* contents)
{
  this->max_hp_ = hp;
  this->now_hp_ = hp;
  this->life_time_ = life_time;
  this->contents_ = contents;
  this->OnHpChanged();
}

void ItemBox::OnHitToPlayer(Player* player)
{
  // ->now_hp_ = (T_UINT16)std::max(0.0f, (T_FLOAT)this->now_hp_ - player->GetVelocityPower() * 0.25f);
  this->OnHpChanged();
}

void ItemBox::OnHpChanged()
{
  if (this->now_hp_ == 0)
  {
    return;
  }
  if (this->life_time_ < BOX_ALERT_LIFETIME)
  {
    this->life_time_ = BOX_ALERT_LIFETIME + BOX_ALERT_GRACE;
    this->SetVisible(true);
  }
}

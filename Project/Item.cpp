#include "Item.h"

static const T_UINT8 ITEM_TEXTURE_X_NUM = 4;
static const T_UINT8 ITEM_TEXTURE_Y_NUM = 4;

static const T_UINT16 ITEM_ALERT_LIFETIME = 100;
static const T_FLOAT DEFAULT_FRICTION = 0.95f;

static const T_UINT16 ITEM_EMISSION_FORCE_BASE = 2;
static const T_UINT16 ITEM_EMISSION_FORCE_FLUCTUATION = 10;

static const T_FLOAT ITEM_GRAVIDATE_POWER = 2.0f;

Item::Item()
  : life_time_(0)
  , velocity_(0.0f, 0.0f, 0.0f)
  , friction_(DEFAULT_FRICTION)
{
}

void Item::OnAllocated()
{
  this->SetVisible(true);
}

void Item::OnFree()
{
  this->SetVisible(false);
}

void Item::Update()
{
  if (!this->IsVisible())
  {
    return;
  }
  this->life_time_--;
  if (this->life_time_ < ITEM_ALERT_LIFETIME)
  {
    this->SetVisible(!this->IsVisible());
  }
  else
  {
    this->SetVisible(true);
  }
  if (this->life_time_ == 0)
  {
    return;
  }
  if (!this->velocity_.IsZero())
  {
    const TVec3f& now_pos = this->GetTransform()->GetPosition();
    this->GetTransform()->SetPosition(now_pos + this->velocity_);
    this->velocity_ *= this->friction_;
    if (this->velocity_.LengthSquare() < 0.25f)
    {
      this->velocity_ *= 0.0f;
    }
  }
  return;
}

void Item::OnHitToPlayer(Player* player)
{
  this->data_->attribute->OnHitToPlayer(player);
  this->SetVisible(false);
}

void Item::AddEmissionForce(T_FLOAT unit_x, T_FLOAT unit_y)
{
  const T_UINT16 rate = ITEM_EMISSION_FORCE_BASE + (rand() % ITEM_EMISSION_FORCE_FLUCTUATION);
  const T_FLOAT x = unit_x * rate;
  const T_FLOAT y = unit_y * rate;
  this->AddForce(x, y);
}

void Item::Gravitate(GameEntity* entity)
{
  const T_FLOAT self_x = this->GetTransform()->GetX();
  const T_FLOAT self_y = this->GetTransform()->GetY();
  const T_FLOAT other_x = entity->GetTransform()->GetX();
  const T_FLOAT other_y = entity->GetTransform()->GetY();
  const T_FLOAT angle = (T_FLOAT)atan2(other_y - self_y, other_x - self_x);
  this->AddForce(cos(angle) * ITEM_GRAVIDATE_POWER, sin(angle) * ITEM_GRAVIDATE_POWER);
}

void Item::AddForce(T_FLOAT x, T_FLOAT y)
{
  this->velocity_.x += x;
  this->velocity_.y += y;
}

void Item::Spawn(const ItemData* data)
{
  this->data_ = data;
  this->SetVisible(true);
  this->life_time_ = this->data_->life_time;
}
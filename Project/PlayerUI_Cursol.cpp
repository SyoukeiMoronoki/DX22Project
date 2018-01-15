#include "PlayerUI_Cursol.h"
#include "Asset.h"

static const T_FLOAT HIT_RADIUS = 16;

static const T_UINT8 SCALING_DURATION = 10;

PlayerUI_Cursol::PlayerUI_Cursol()
  : scaling_duration_(0)
  , position_(0.0f, 0.0f)
  , position_changed_(true)
{
  this->sprite_ = AnimatedSprite::CreateWithTexture(&Asset::Texture::PLAYER_TURGET, 2, 2);
  this->sprite_->GetTiledTextureRegion()->SetXNum(2);
  this->sprite_->GetTiledTextureRegion()->SetYNum(2);
  this->sprite_->GetTiledTextureRegion()->FitToTexture();
  this->sprite_->FitToTexture();
  this->sprite_->Animate(6);
  this->AddChild(this->sprite_);
  this->position_ = TVec2f(0.0f, 0.0f);
  this->scaling_duration_ = 0;
  this->position_changed_ = true;
}

PlayerUI_Cursol::~PlayerUI_Cursol()
{
  if (this->sprite_)
  {
    delete this->sprite_;
  }
}

void PlayerUI_Cursol::Update()
{
  if (this->scaling_duration_ == 0)
  {
    this->GetTransform()->SetScale(1.0f);
    return;
  }
  const T_FLOAT rate = (1.0f - (T_FLOAT)scaling_duration_ / SCALING_DURATION) * 2.0f - 1.0f;
  this->GetTransform()->SetScale((1.5f - rate * rate) );
  this->scaling_duration_--;
}

void PlayerUI_Cursol::OnAttack()
{
  if (this->scaling_duration_ > 0)
  {
    return;
  }
  this->scaling_duration_ = SCALING_DURATION;
}


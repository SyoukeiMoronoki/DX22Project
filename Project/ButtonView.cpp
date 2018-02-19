#include "ButtonView.h"
#include "Asset.h"

ButtonView::ButtonView(T_UINT8 button_id, T_FLOAT size)
  : id_(button_id)
{
  this->bg_ = Sprite::CreateWithTexture(Asset::Texture::UI_KEYBOARD);
  this->bg_->GetTextureRegion()->SetWidth(128);
  this->bg_->GetTextureRegion()->SetHeight(128);
  this->bg_->FitToTexture();
  this->AddChild(this->bg_);

  this->light_ = Sprite::CreateWithTexture(Asset::Texture::UI_KEYBOARD);
  this->light_->GetTextureRegion()->SetWidth(64);
  this->light_->GetTextureRegion()->SetHeight(64);
  this->light_->GetTextureRegion()->SetX(0);
  this->light_->GetTextureRegion()->SetY(128);
  this->light_->GetTransform()->SetScale(2.0f);
  this->light_->GetMaterial()->SetDiffuse(1.0f, 1.0f, 1.0f, 0.0f);
  this->light_->FitToTexture();
  this->AddChild(this->light_);

  this->char_ = Sprite::CreateWithTexture(Asset::Texture::UI_KEYBOARD);
  if (button_id == BUTTON_L_SHIFT)
  {
    this->bg_->GetTransform()->SetScaleX(2.0f);
    this->light_->GetTransform()->SetScaleX(4.0f);
    this->char_->GetTextureRegion()->SetWidth(128);
    this->char_->GetTextureRegion()->SetHeight(64);
    this->char_->GetTextureRegion()->SetX(0);
    this->char_->GetTextureRegion()->SetY(128 + 64);
  }
  else
  {
    this->char_->GetTextureRegion()->SetWidth(64);
    this->char_->GetTextureRegion()->SetHeight(64);
    this->char_->GetTextureRegion()->SetX(128 + (button_id % 2) * 64);
    this->char_->GetTextureRegion()->SetY((button_id / 2) * 64);
  }
  this->char_->FitToTexture();
  this->AddChild(this->char_);

  T_FLOAT scale = size / 128.0f;
  
  this->GetTransform()->SetScale(scale);

  EntityModifier* m00 = EntityModifierFactory::ScaleTo(5, scale * 0.8f);
  EntityModifier* m01 = EntityModifierFactory::ScaleTo(5, scale);
  EntityModifier* m0 = EntityModifierFactory::Sequence(m00, m01);
  this->scale_modifier_ = EntityModifierFactory::Root(m0);
  this->scale_modifier_->Retain();
  this->scale_modifier_->Stop();
  this->RegisterEntityModifier(this->scale_modifier_);

  EntityModifier* m10 = EntityModifierFactory::ColorToAlpha(5, 1.0f);
  EntityModifier* m11 = EntityModifierFactory::ColorToAlpha(5, 0.0f);
  EntityModifier* m1 = EntityModifierFactory::Sequence(m10, m11);
  this->light_modifier_ = EntityModifierFactory::Root(m1);
  this->light_modifier_->Retain();
  this->light_modifier_->Stop();
  this->light_->RegisterEntityModifier(this->light_modifier_);
}

ButtonView::~ButtonView()
{
  delete this->bg_;
  delete this->light_;
  delete this->char_;
  this->scale_modifier_->Release();
  this->light_modifier_->Release();
}

void ButtonView::Update()
{
  bool on_pressed = false;
  switch (this->id_)
  {
  case BUTTON_A:
    on_pressed = HalEngine::Input(0)->GetAxisDown(GameInput::X_AXIS) < 0;
    break;
  case BUTTON_S:
    on_pressed = HalEngine::Input(0)->GetAxisDown(GameInput::Y_AXIS) < 0;
    break;
  case BUTTON_D:
    on_pressed = HalEngine::Input(0)->GetAxisDown(GameInput::X_AXIS) > 0;
    break;
  case BUTTON_W:
    on_pressed = HalEngine::Input(0)->GetAxisDown(GameInput::Y_AXIS) > 0;
    break;
  case BUTTON_K:
    on_pressed = HalEngine::Input(0)->GetButtonDown(GameInput::FIRE);
    break;
  case BUTTON_L:
    on_pressed = HalEngine::Input(0)->GetButtonDown(GameInput::SCOPE);
    break;
  case BUTTON_SEMI:
    //on_pressed = HalEngine::Input(0)->GetButtonDown(GameInput::FOCUS);
    break;
  case BUTTON_O:
    on_pressed = HalEngine::Input(0)->GetButtonDown(GameInput::EYE);
    break;
  case BUTTON_L_SHIFT:
    on_pressed = HalEngine::Input(0)->GetButtonDown(GameInput::FOCUS);
    break;
  default:
    break;
  }
  if (on_pressed)
  {
    this->scale_modifier_->Play();
    this->light_modifier_->Play();
  }
}

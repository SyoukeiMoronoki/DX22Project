#include "Tutorial.h"
#include "Asset.h"
#include "GameSceneDirector.h"

static const T_UINT8 START_TUTORIAL_BEGIN = Tutorial::TUTORIAL_MOVE;
static const T_UINT8 START_TUTORIAL_END = Tutorial::TUTORIAL_SONAR_COMMENT;
static const T_UINT8 START_TUTORIAL_COUNT = START_TUTORIAL_END - START_TUTORIAL_BEGIN + 1;

Tutorial::Tutorial()
{
  this->sprite_ = AnimatedSprite::CreateWithTexture(Asset::Texture::TEXT_TUTORIAL, 1, TUTORIAL_DATANUM);
  this->AddChild(this->sprite_);
  this->sprite_->GetMaterial()->SetDiffuse(1.0f, 1.0f, 1.0f, 0.0f);

  EntityModifier* m00 = EntityModifierFactory::ColorFromToAlpha(10, 0.0f, 1.0f);
  EntityModifier* m01 = EntityModifierFactory::TranslateFromToY(10, -40.0f, 0.0f);
  m01->SetEasingFunction(EasingFunction::FK_EXPONENTIAL, EasingFunction::EASE_IN);
  EntityModifier* m0 = EntityModifierFactory::Synchronized(m00, m01);
  EntityModifier* m1 = EntityModifierFactory::Delay(100);
  EntityModifier* m2 = EntityModifierFactory::Sequence(m0, m1);
  EntityModifier* m3 = EntityModifierFactory::Round(m2);
  this->modifier_ = EntityModifierFactory::Root(m3);
  this->modifier_->Retain();
  this->modifier_->Stop();
  this->sprite_->RegisterEntityModifier(this->modifier_);

  this->current_tutorial_ = -1;
  this->show_boss_message_ = false;
  this->show_cant_target_message_ = false;
}

Tutorial::~Tutorial()
{
  delete this->sprite_;
  this->modifier_->Release();
}

void Tutorial::Update()
{
  if (GameSceneDirector::GetInstance().IsGameOver())
  {
    return;
  }
  if (GameSceneDirector::GetInstance().GetCurrentPhase() == GameConstants::PHASE_START)
  {
    T_FLOAT progress = GameSceneDirector::GetInstance().GetTimeProgress();
    T_FLOAT d = 1.0f / START_TUTORIAL_COUNT;
    T_FLOAT next = d * (this->current_tutorial_ + 1);
    if (progress > next)
    {
      this->current_tutorial_++;
      this->sprite_->SetCurrentIndex(this->current_tutorial_);
      this->modifier_->Play();
    }
  }
  T_FLOAT progress = GameSceneDirector::GetInstance().GetTimeProgress();
  if (GameSceneDirector::GetInstance().GetCurrentPhase() == GameConstants::PHASE_BOSS)
  {
    if (progress > GameConstants::CAN_LOCKON_PROGRESS && !this->show_boss_message_)
    {
      this->sprite_->SetCurrentIndex(TUTORIAL_LOCK_ON);
      this->modifier_->Play();
      this->show_boss_message_ = true;
    }
  }
  if (GameSceneDirector::GetInstance().GetCurrentPhase() == GameConstants::PHASE_DARK)
  {
    if (progress > GameConstants::CANT_LOCKON_PROGRESS && !this->show_cant_target_message_)
    {
      this->sprite_->SetCurrentIndex(TUTORIAL_CANT_LOCK_ON);
      this->modifier_->Play();
      this->show_cant_target_message_ = true;
    }
  }
}

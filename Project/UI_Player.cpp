#include "UI_Player.h"
#include "GameSceneDirector.h"
#include "GameConstants.h"
#include "Asset.h"

static const T_UINT8 SCORE_DIGIT_COUNT = 8;
static const T_FLOAT SCORE_WIDTH = 256.0f;

static const T_UINT8 TIMER_DIGIT_COUNT = 3;
static const T_FLOAT TIMER_WIDTH = 128.0f;

static const T_FLOAT EAR_GAGUGE_WIDTH = 512.0f;
static const T_FLOAT EAR_GAGUGE_HEIGHT = 32.0f;

static const T_FLOAT HP_GAGUGE_WIDTH = 512.0f;
static const T_FLOAT HP_GAGUGE_HEIGHT = 32.0f;

UI_Player::UI_Player()
{
  const T_FLOAT width = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
  const T_FLOAT height = (T_FLOAT)Director::GetInstance()->GetScreenHeight();
  
  this->time_view_ = new NumberView(TIMER_DIGIT_COUNT, TIMER_WIDTH);
  this->time_view_->GetTransform()->SetPositon(width * 0.3f, height * 0.4f);
  this->AddChild(this->time_view_);

  this->score_view_ = new NumberView(SCORE_DIGIT_COUNT, SCORE_WIDTH);
  this->score_view_->SetDuration(5);
  this->score_view_->GetTransform()->SetPositon(-width * 0.4f, height * 0.4f);
  this->AddChild(this->score_view_);

  this->ear_gauge_ = new Gauge(&Asset::Texture::UI_EARGAUGE, EAR_GAGUGE_WIDTH, EAR_GAGUGE_HEIGHT);
  this->ear_gauge_->SetMaxValue(GameConstants::EYE_GAUGE_MAX);
  this->ear_gauge_->GetTransform()->SetPositon(-width * 0.4f, -height * 0.4f);
  this->AddChild(this->ear_gauge_);

  this->hp_gauge_ = new Gauge(&Asset::Texture::UI_HPGAUGE, HP_GAGUGE_WIDTH, HP_GAGUGE_HEIGHT);
  this->hp_gauge_->SetMaxValue(GameConstants::HP_MAX);
  this->hp_gauge_->GetTransform()->SetPositon(-width * 0.4f, -height * 0.35f);
  this->AddChild(this->hp_gauge_);
}

UI_Player::~UI_Player()
{
  if (this->time_view_)
  {
    delete this->time_view_;
  }
  if (this->score_view_)
  {
    delete this->score_view_;
  }
  if (this->ear_gauge_)
  {
    delete this->ear_gauge_;
  }
  if (this->hp_gauge_)
  {
    delete this->hp_gauge_;
  }
}

void UI_Player::GameInit()
{
  this->time_view_->ViewInit(0);
  this->score_view_->ViewInit(0);
  this->hp_gauge_->ViewInit(GameConstants::HP_MAX, GameConstants::HP_MAX);
  this->ear_gauge_->ViewInit(GameConstants::EYE_GAUGE_MAX, 0);
}

void UI_Player::Update()
{
  this->time_view_->Update();
  this->score_view_->SetValue(GameSceneDirector::GetInstance().GetScore());
  this->score_view_->Update();

  this->ear_gauge_->Update();

  this->hp_gauge_->Update();
}

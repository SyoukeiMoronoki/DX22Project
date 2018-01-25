#include "UI_Player.h"
#include "GameSceneDirector.h"
#include "GameConstants.h"
#include "Asset.h"

struct ButtonProperty
{
  ButtonView::ButtonID id;
  TVec2f pos;
};

static const ButtonProperty LEFT_BUTTON_PROPERTIES[4] =
{
  { ButtonView::BUTTON_A,{ -1.0f, 0.0f } },
  { ButtonView::BUTTON_S,{  0.0f, 0.0f } },
  { ButtonView::BUTTON_D,{  1.0f, 0.0f } },
  { ButtonView::BUTTON_W,{  0.0f, 1.0f } },
};

static const ButtonProperty RIGHT_BUTTON_PROPERTIES[4] = 
{
  { ButtonView::BUTTON_K,{ -1.0f, 0.0f } },
  { ButtonView::BUTTON_L,{  0.0f, 0.0f } },
  { ButtonView::BUTTON_SEMI,{  1.0f, 0.0f } },
  { ButtonView::BUTTON_O,{  0.0f, 1.0f } },
};

static const T_FLOAT BUTTON_SIZE = 64.0f;

static const T_FLOAT L_SHIFT_BUTTON_SIZE = 64.0f;

static const T_UINT8 SCORE_DIGIT_COUNT = 8;
static const T_FLOAT SCORE_WIDTH = 256.0f;

static const T_UINT8 TIMER_DIGIT_COUNT = 3;
static const T_FLOAT TIMER_WIDTH = 128.0f;

static const T_FLOAT EAR_GAGUGE_WIDTH = 400.0f;
static const T_FLOAT EAR_GAGUGE_HEIGHT = 16.0f;

static const T_FLOAT HP_GAGUGE_WIDTH = 400.0f;
static const T_FLOAT HP_GAGUGE_HEIGHT = 16.0f;

UI_Player::UI_Player()
{
  const T_FLOAT width = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
  const T_FLOAT height = (T_FLOAT)Director::GetInstance()->GetScreenHeight();
  
  this->time_view_ = new NumberView(TIMER_DIGIT_COUNT, TIMER_WIDTH);
  this->time_view_->GetTransform()->SetPositon(width * 0.35f, height * 0.325f);
  this->AddChild(this->time_view_);

  this->score_view_ = new NumberView(SCORE_DIGIT_COUNT, SCORE_WIDTH);
  this->score_view_->SetDuration(5);
  this->score_view_->GetTransform()->SetPositon(width * 0.45f - SCORE_WIDTH, height * 0.4f);
  this->AddChild(this->score_view_);

  this->ear_gauge_ = new Gauge(&Asset::Texture::UI_EARGAUGE, EAR_GAGUGE_WIDTH, EAR_GAGUGE_HEIGHT);
  this->ear_gauge_->SetMaxValue(GameConstants::EYE_GAUGE_MAX);
  this->ear_gauge_->GetTransform()->SetPositon(-width * 0.45f, height * 0.40f);
  this->AddChild(this->ear_gauge_);

  this->hp_gauge_ = new Gauge(&Asset::Texture::UI_HPGAUGE, HP_GAGUGE_WIDTH, HP_GAGUGE_HEIGHT);
  this->hp_gauge_->SetMaxValue(GameConstants::HP_MAX);
  this->hp_gauge_->GetTransform()->SetPositon(-width * 0.45f, height * 0.425f);
  this->AddChild(this->hp_gauge_);

  for (T_UINT8 i = 0; i < 4; ++i)
  {
    this->left_buttons_[i] = new ButtonView(LEFT_BUTTON_PROPERTIES[i].id, BUTTON_SIZE);
    TVec2f pos = LEFT_BUTTON_PROPERTIES[i].pos * BUTTON_SIZE;
    this->left_buttons_[i]->GetTransform()->SetPositon(-width * 0.375f + pos.x, -height * 0.35f + pos.y);
    this->AddChild(this->left_buttons_[i]);
  }

  for (T_UINT8 i = 0; i < 4; ++i)
  {
    this->right_buttons_[i] = new ButtonView(RIGHT_BUTTON_PROPERTIES[i].id, BUTTON_SIZE);
    TVec2f pos = RIGHT_BUTTON_PROPERTIES[i].pos * BUTTON_SIZE;
    this->right_buttons_[i]->GetTransform()->SetPositon(width * 0.375f + pos.x, -height * 0.35f + pos.y);
    this->AddChild(this->right_buttons_[i]);
  }

  this->l_shift_button_ = new ButtonView(ButtonView::BUTTON_L_SHIFT, BUTTON_SIZE);
  this->l_shift_button_->GetTransform()->SetPositon(-width * 0.425f, -height * 0.35f - BUTTON_SIZE);
  this->AddChild(this->l_shift_button_);
}

UI_Player::~UI_Player()
{
  delete this->time_view_;
  delete this->score_view_;
  delete this->ear_gauge_;
  delete this->hp_gauge_;
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

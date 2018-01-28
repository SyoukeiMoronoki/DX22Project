#include "ResultScene.h"
#include "GameSceneDirector.h"
#include "EngineSetting.h"

#include "TitleScene.h"
#include "Asset.h"
#include "GameInput.h"

static const T_UINT8 SCORE_DIGIT_COUNT = 8;
static const T_FLOAT SCORE_WIDTH = 256.0f;

static const T_UINT8 BONUS_DIGIT_COUNT = 8;
static const T_FLOAT BONUS_WIDTH = 256.0f;

static const T_UINT8 TOTAL_SCORE_DIGIT_COUNT = 8;
static const T_FLOAT TOTAL_SCORE_WIDTH = 256.0f;

void ResultScene::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Texture::FIELD_GROUND);
  resource->ReserveLoad(Asset::Texture::FONT_NUMBER);
  resource->ReserveLoad(Asset::Texture::TEXT_SCORE);
  resource->ReserveLoad(Asset::Texture::TEXT_BONUS);
  resource->ReserveLoad(Asset::Texture::TEXT_RESULT);
}

void ResultScene::OnSetup()
{
  this->camera2d_ = new Camera2D();
  this->AddCamera(this->camera2d_);

  this->score_view_ = new NumberView(SCORE_DIGIT_COUNT, SCORE_WIDTH);
  this->bonus_view_ = new NumberView(BONUS_DIGIT_COUNT, BONUS_WIDTH);
  this->total_score_view_ = new NumberView(TOTAL_SCORE_DIGIT_COUNT, TOTAL_SCORE_WIDTH);

  this->score_view_->SetDuration(60);
  this->bonus_view_->SetDuration(60);
  this->total_score_view_->SetDuration(60);

  this->score_view_->GetTransform()->SetY(150);
  this->bonus_view_->GetTransform()->SetY(0);
  this->total_score_view_->GetTransform()->SetY(-150);

  this->score_text_ = Sprite::CreateWithTexture(&Asset::Texture::TEXT_SCORE);
  this->bonus_text_ = Sprite::CreateWithTexture(&Asset::Texture::TEXT_BONUS);
  this->total_score_text_ = Sprite::CreateWithTexture(&Asset::Texture::TEXT_RESULT);

  this->score_text_->GetTransform()->SetX(-200);
  this->bonus_text_->GetTransform()->SetX(-200);
  this->total_score_text_->GetTransform()->SetX(-200);

  this->score_text_->GetTransform()->SetY(150);
  this->bonus_text_->GetTransform()->SetY(0);
  this->total_score_text_->GetTransform()->SetY(-150);

  this->score_text_->GetTransform()->SetScale(0.4f);
  this->bonus_text_->GetTransform()->SetScale(0.8f, 0.4f);
  this->total_score_text_->GetTransform()->SetScale(0.4f);

  this->AddChild(this->score_text_);
  this->AddChild(this->bonus_text_);
  this->AddChild(this->total_score_text_);

  this->AddChild(this->score_view_);
  this->AddChild(this->bonus_view_);
  this->AddChild(this->total_score_view_);
}

void ResultScene::OnUnload()
{
  delete this->total_score_text_;
  delete this->bonus_text_;
  delete this->score_text_;
  delete this->total_score_view_;
  delete this->score_view_;
  delete this->bonus_view_;
  delete this->camera2d_;
}

void ResultScene::OnShow(ISceneShowListener* listener)
{
  this->score_view_->ViewInit(0);
  this->bonus_view_->ViewInit(0);
  this->total_score_view_->ViewInit(0);

  this->StartScoreCount();
}

void ResultScene::OnHide(ISceneHideListener* listener)
{
}

void ResultScene::Update()
{
  this->EngineInput();

  if (this->score_view_->IsAnimated())
  {
    this->score_view_->Update();
    if (!this->score_view_->IsAnimated())
    {
      this->StartBonusCount();
    }
    return;
  }
  if (this->bonus_view_->IsAnimated())
  {
    this->bonus_view_->Update();
    if (!this->bonus_view_->IsAnimated())
    {
      this->StartTotalScoreCount();
    }
    return;
  }
  if (this->total_score_view_->IsAnimated())
  {
    this->total_score_view_->Update();
    return;
  }
}

void ResultScene::EngineInput()
{
  if (!HalEngine::Input(0)->AnyButtonDown())
  {
    return;
  }
  if (this->score_view_->IsAnimated())
  {
    this->score_view_->AnimationFinish();
    this->StartBonusCount();
    return;
  }
  if (this->bonus_view_->IsAnimated())
  {
    this->bonus_view_->AnimationFinish();
    this->StartTotalScoreCount();
    return;
  }
  if (this->total_score_view_->IsAnimated())
  {
    this->total_score_view_->AnimationFinish();
    return;
  }
  Director::GetInstance()->ChangeScene(new TitleScene());
}

void ResultScene::StartScoreCount()
{
  this->score_view_->SetValue(GameSceneDirector::GetInstance().GetScore());
}

void ResultScene::StartBonusCount()
{
  T_UINT32 bonus = GameSceneDirector::GetInstance().GetBonus();
  if (bonus == 0)
  {
    this->StartTotalScoreCount();
    return;
  }
  this->bonus_view_->SetValue(bonus);
}

void ResultScene::StartTotalScoreCount()
{
  this->total_score_view_->SetValue(GameSceneDirector::GetInstance().GetScore() + GameSceneDirector::GetInstance().GetBonus());
}

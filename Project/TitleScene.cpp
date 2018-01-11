#include "TitleScene.h"

#include "GameScene.h"
#include "EngineSetting.h"

#include "Asset.h"
#include "GameInput.h"
#include "InitScene.h"

static const T_FLOAT NEAR = 128.0f;
static const T_FLOAT FAR = 1024.0f;
static const T_FLOAT VIEWING_ANGLE = MathConstants::PI_2 / 3.0f;

void TitleScene::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Model::SKYBOX);

  resource->ReserveLoad(Asset::Texture::TEXT_TITLE);
  resource->ReserveLoad(Asset::Texture::TEXT_PRESSBUTTON);
}

void TitleScene::OnSetup()
{
  this->camera_ = new Camera2D();
  this->camera_->GetRenderState()->AddTargetLayerId(0);
  this->AddCamera(this->camera_);

  this->title_ = Sprite::CreateWithTexture(&Asset::Texture::TEXT_TITLE);
  this->title_->GetTransform()->SetY(100);

  this->press_a_button_ = Sprite::CreateWithTexture(&Asset::Texture::TEXT_PRESSBUTTON);
  this->press_a_button_->GetTransform()->SetY(-200);
  this->press_a_button_->GetTransform()->SetScale(0.5f);
  
  //this->AddChild(this->title_);
  this->AddChild(this->press_a_button_);

  //this->cube_ = new Cube3D();
  //this->cube_->SetLightingEnabled(false);
  //this->cube_->GetTransform()->SetZ(10.0f);
  //this->cube_->GetTransform()->SetScale(1.0f);
  //this->AddChild(this->cube_);

  //Camera3D* camera3D = new Camera3D();
  //camera3D->GetRenderState()->AddTargetLayerId(0);
  //camera3D->SetEnabled(true);
  //this->AddCamera(camera3D);

  //Model* skydome = new Model(Asset::Model::SKYBOX);
  //skydome->SetLightingEnabled(false);
  //this->AddChild(skydome);
}

void TitleScene::OnUnload()
{
  //if (this->press_a_button_)
  //{
  //  delete this->press_a_button_;
  //  this->press_a_button_ = NULL;
  //}
}

void TitleScene::OnShow(ISceneShowListener* listener)
{
}

void TitleScene::OnHide(ISceneHideListener* listener)
{
}

void TitleScene::Update()
{
  static int cnt = 0;
  //this->viewport_->SetCameraAngleDeg(cnt * 0.25f);
  this->press_a_button_->SetVisible((cnt / 30) % 2 == 0);
  cnt++;  
  using namespace EngineInput;
  //if (HalEngine::Input(0)->GetButtonDown(GameInput::FIRE))
  if (HalEngine::Input(0)->AnyButtonDown())
  {
    Director::GetInstance()->ChangeScene(new InitScene());
    return;
  }
}

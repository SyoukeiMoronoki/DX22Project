#include "TestScene2.h"
#include "TestScene.h"
#include "GameInput.h"
#include "Asset.h"

void TestScene2::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Texture::FIELD_BOYA);
}

void TestScene2::OnSetup()
{
  Camera2D* camera = new Camera2D();
  camera->GetRenderState()->AddTargetLayerId(0);
  this->AddCamera(camera);
  Sprite* sprite = Sprite::CreateWithTexture(&Asset::Texture::FIELD_BOYA);
  this->AddChild(sprite);
}

void TestScene2::OnUnload()
{
}

void TestScene2::OnShow(ISceneShowListener* listener)
{
}

void TestScene2::OnHide(ISceneHideListener* listener)
{
}

void TestScene2::Update()
{
  Director::GetInstance()->ChangeScene(new TestScene());
  //if (HalEngine::Input(0)->AnyButtonDown())
  //{
  //  Director::GetInstance()->ChangeScene(new TestScene());
  //}
}

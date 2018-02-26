#include "TestScene.h"
#include "TestScene2.h"
#include "GameInput.h"
#include "Asset.h"

void TestScene::OnLoad(IResourceLoadReserver* resource)
{
//  resource->ReserveLoad(Asset::Texture::FIELD_BOYA);
  resource->ReserveLoad(Asset::Texture::FIELD_GROUND);
}

void TestScene::OnSetup()
{
}

void TestScene::OnUnload()
{
}

void TestScene::OnShow(ISceneShowListener* listener)
{
}

void TestScene::OnHide(ISceneHideListener* listener)
{
}

void TestScene::Update()
{
  Director::GetInstance()->ChangeScene(new TestScene2());
  //if (HalEngine::Input(0)->AnyButtonDown())
  //{
  //  Director::GetInstance()->ChangeScene(new TestScene2());
  //}
}

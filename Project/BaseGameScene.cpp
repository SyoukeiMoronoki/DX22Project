#include "BaseGameScene.h"
#include "GameDirector.h"

BaseGameScene::BaseGameScene(GameSetting* setting)
{
  this->manager_ = new GameManager(this);
}

void BaseGameScene::OnLoad(IResourceLoadReserver* resource)
{
  this->manager_->OnLoad(resource);
}

void BaseGameScene::OnSetup()
{
  this->manager_->OnSetup();
}

void BaseGameScene::OnUnload()
{
  this->manager_->OnUnload();
}

void BaseGameScene::OnShow(ISceneShowListener* listener)
{
  listener->ControlShowFinish();
  listener->OnShowFinish();
}

void BaseGameScene::OnShowFinish()
{
  this->manager_->GameStart();
}

void BaseGameScene::OnHide(ISceneHideListener* listener)
{
  listener->ControlHideFinish();
  listener->OnHideFinish();
}

void BaseGameScene::OnHideFinish()
{
  this->manager_->End();
}

void BaseGameScene::PreUpdate()
{
  this->manager_->PreUpdate();
}

void BaseGameScene::Update()
{
  this->manager_->Update();
}

void BaseGameScene::PostUpdate()
{
  this->manager_->PostUpdate();
}

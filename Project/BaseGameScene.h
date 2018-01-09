#pragma once

#include <HalEngine.h>
#include "GameManager.h"
#include "GameSetting.h"

class BaseGameScene : public Scene
{
public:
  BaseGameScene(GameSetting* setting);

protected:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnShowFinish() override;
  virtual void OnHide(ISceneHideListener* listener) override;
  virtual void OnHideFinish() override;

public:
  void PreUpdate() override;
  void Update() override;
  void PostUpdate() override;

protected:
  GameManager* manager_;
  

};
#pragma once

#include <HalEngine.h>

class InitScene : public Scene
{
public:
  InitScene();

public:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

public:
  void Update() override;

};

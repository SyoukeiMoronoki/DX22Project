#pragma once

#include <HalEngine.h>

class TestScene2 : public Scene
{
protected:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

  void Update() override;
};
#pragma once

#include <vector>
#include <HalEngine.h>

class TitleScene : public Scene
{
public:
  virtual void OnLoad(IResourceLoadReserver* order) override;
  virtual void OnSetup();
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

};
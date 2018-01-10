#pragma once

#include <HalEngine.h>

class TitleScene : public Scene
{
public:
  // Scene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

  virtual void Update() override;

private:
  Camera2D* camera_;

  Sprite* title_;
  Sprite* press_a_button_;
};
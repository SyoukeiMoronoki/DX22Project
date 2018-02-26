#pragma once

#include <HalEngine.h>

class TestScene3 : public Scene
{
protected:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

private:
  Camera3D_LookAt* camera_;
  Cube3D* cube_;
};
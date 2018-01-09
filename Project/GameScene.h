#pragma once

#include <HalEngine.h>
#include "PlayerManager.h"
#include "StarManager.h"

class GameScene : public Scene
{
public:
  GameScene();
  ~GameScene();

public:
  // Scene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

  virtual void Update() override;

private:
  PlayerManager* player_manager_;
  StarManager* star_manager_;
  Model* skydome_;

};
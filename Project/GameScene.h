#pragma once

#include <HalEngine.h>

#include "UI_Cursol.h"

class Player;
class EnemyManager;
class UI_Player;

class GameScene : public Scene
{
public:
  GameScene();

protected:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

public:
  virtual void Update() override;

private:
  Camera2D* camera2d_;

  Player* player_;
  EnemyManager* enemy_manager_;

  MeshField* field_;

  UI_Player* ui_player_;
  UI_Cursol* ui_cursol_;

  Sprite* boya_;
  Sprite* text_time_up_;

  T_UINT8 timeup_text_show_time_;
  T_UINT8 grand_slam_count_;
  T_UINT8 weak_happy_count_;
  T_UINT8 damage_count_;
  T_UINT16 time_count_;
};

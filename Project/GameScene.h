#pragma once

#include <HalEngine.h>

#include "Field.h"

class Player;
class EnemyManager;
class UI_Player;
class BossController;

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
  BossController* boss_controller_;

  Field* field_;

  UI_Player* ui_player_;

  Sprite* boya_;
  Sprite* text_time_up_;

  T_UINT8 timeup_text_show_time_;
  T_UINT8 grand_slam_count_;
  T_UINT8 weak_happy_count_;
  T_UINT8 damage_count_;
  T_UINT16 time_count_;
};

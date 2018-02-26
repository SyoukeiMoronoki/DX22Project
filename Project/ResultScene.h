#pragma once

#include <HalEngine.h>
#include "NumberView.h"

class ResultScene : public Scene
{
public:
  void OnLoad(IResourceLoadReserver* resource) override;
  void OnSetup() override;
  void OnUnload() override;
  void OnShow(ISceneShowListener* listener) override;
  void OnHide(ISceneHideListener* listener) override;

public:
  void Update() override;
  void EngineInput();

private:
  void StartScoreCount();
  void StartBonusCount();
  void StartTotalScoreCount();

private:
  Camera2D* camera2d_;

  NumberView* score_view_;
  NumberView* bonus_view_;
  NumberView* total_score_view_;

  Sprite* score_text_;
  Sprite* bonus_text_;
  Sprite* total_score_text_;

};
#pragma once

#include "GameSetting.h"

/*
  ゲームのライフサイクルは以下の通り

  (1)
    GameManager::Start();が呼ばれたら
    <直前のシーンからの遷移処理>
      直前のScene::OnHide();
      直前のScene::OnHideFinish();
      <ローディング画面で行われる処理>
        直前のScene::OnUnload();
        BaseGameScene::OnLoad();
        BaseGameScene::OnSetup();
        GameManager::OnSetup();
      <ローディング画面で行われる処理/>
      BaseGameScene::OnShow();
      BaseGameScene::OnShowFinish();
      GameManager::GameStart();
    <直前のシーンからの遷移処理/>

  (2)
    <ゲームループ処理>
      BaseGameScene::PreUpdate();
      GameManager::PreUpdate();
      SceneのChildrenのPreUpdate();

      BaseGameScene::Update();
      GameManager::Update();
      SceneのChildrenのUpdate();

      BaseGameScene::PostUpdate();
      GameManager::PostUpdate();
      SceneのChildrenのPostUpdate();
    <ゲームループ処理/>

  (3)
    !--ゲームループ処理中にGameManager::GamePause();が呼ばれたら
    <ポーズ時ループ処理>
      BaseGameScene::PreUpdate();
      GameManager::PreUpdate();
      SceneのChildrenのPreUpdate();

      BaseGameScene::Update();
      GameManager::Update();
      SceneのChildrenのUpdate();

      BaseGameScene::PostUpdate();
      GameManager::PostUpdate();
      SceneのChildrenのPostUpdate();
    <ポーズ時ループ処理/>
    !--ポーズ時ループ処理中にGameManager::GameResume();が呼ばれたら
    !--ゲームループ処理に戻る

  (4)
    !--ゲームループ処理中にGameManager::ToResult();が呼ばれたら
    <リザルト画面ループ処理>
      BaseGameScene::PreUpdate();
      GameManager::PreUpdate();
      SceneのChildrenのPreUpdate();

      BaseGameScene::Update();
      GameManager::Update();
      SceneのChildrenのUpdate();

      BaseGameScene::PostUpdate();
      GameManager::PostUpdate();
      SceneのChildrenのPostUpdate();
    <リザルト画面ループ処理/>
    !--リザルト画面ループ処理中にGameManager::GameEnd(Scene*);が呼ばれたら
    <引数で指定したSceneへの(次Scene)遷移処理>
      BaseGameScene::OnHide();
      BaseGameScene::OnHideFinish();
      GameManager::End();
      <ローディング画面で行われる処理>
        BaseGameScene::OnUnload();
        GameManager::OnUnload();
        次Scene::OnLoad();
        次Scene::OnSetup();
      <ローディング画面で行われる処理/>
      次Scene::OnShow();
      次Scene::OnShowFinish();
    <引数で指定したSceneへの(次Scene)遷移処理/>

  (5)
    !--Start(GameSetting* setting)時、すでにゲームが起動していた場合
    GameSetting
*/

/*
  ゲーム処理はScene側の処理に依存させない。
  DebugSceneを作る際の利便性を考えて作成する
*/
class GameManager
{
public:
  enum GameState
  {
    GAME_SHOWING,
    GAME_LOOP,
    GAME_PAUSE,
    GAME_RESULT,
    GAME_HIDING,
  };

public:
  GameManager(Scene* scene);
  ~GameManager();

public:
  void OnLoad(IResourceLoadReserver* resource);
  void OnSetup();
  void OnUnload();

  //ゲーム開始。
  //ゲーム設定を変えて開始しなおす事も可能。
  void Start(GameSetting* setting);
  void GameStart();

  void PreUpdate();
  void Update();
  void PostUpdate();

  //ゲームの一時停止
  void GamePause();

  //ゲームの再開
  void GameResume();
 
  //ゲーム終了後処理（リザルトなど）
  void ToResult();

  //ゲーム終了処理。
  void GameEnd(Scene* next_scene);

  //全ての処理の終了後処理
  void End();
  
public:
  inline GameState GetGameState() const
  {
    return this->state_;
  }

private:
  Scene* scene_;
  GameState state_;
};
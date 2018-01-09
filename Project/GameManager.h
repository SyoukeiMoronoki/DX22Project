#pragma once

#include "GameSetting.h"

/*
  �Q�[���̃��C�t�T�C�N���͈ȉ��̒ʂ�

  (1)
    GameManager::Start();���Ă΂ꂽ��
    <���O�̃V�[������̑J�ڏ���>
      ���O��Scene::OnHide();
      ���O��Scene::OnHideFinish();
      <���[�f�B���O��ʂōs���鏈��>
        ���O��Scene::OnUnload();
        BaseGameScene::OnLoad();
        BaseGameScene::OnSetup();
        GameManager::OnSetup();
      <���[�f�B���O��ʂōs���鏈��/>
      BaseGameScene::OnShow();
      BaseGameScene::OnShowFinish();
      GameManager::GameStart();
    <���O�̃V�[������̑J�ڏ���/>

  (2)
    <�Q�[�����[�v����>
      BaseGameScene::PreUpdate();
      GameManager::PreUpdate();
      Scene��Children��PreUpdate();

      BaseGameScene::Update();
      GameManager::Update();
      Scene��Children��Update();

      BaseGameScene::PostUpdate();
      GameManager::PostUpdate();
      Scene��Children��PostUpdate();
    <�Q�[�����[�v����/>

  (3)
    !--�Q�[�����[�v��������GameManager::GamePause();���Ă΂ꂽ��
    <�|�[�Y�����[�v����>
      BaseGameScene::PreUpdate();
      GameManager::PreUpdate();
      Scene��Children��PreUpdate();

      BaseGameScene::Update();
      GameManager::Update();
      Scene��Children��Update();

      BaseGameScene::PostUpdate();
      GameManager::PostUpdate();
      Scene��Children��PostUpdate();
    <�|�[�Y�����[�v����/>
    !--�|�[�Y�����[�v��������GameManager::GameResume();���Ă΂ꂽ��
    !--�Q�[�����[�v�����ɖ߂�

  (4)
    !--�Q�[�����[�v��������GameManager::ToResult();���Ă΂ꂽ��
    <���U���g��ʃ��[�v����>
      BaseGameScene::PreUpdate();
      GameManager::PreUpdate();
      Scene��Children��PreUpdate();

      BaseGameScene::Update();
      GameManager::Update();
      Scene��Children��Update();

      BaseGameScene::PostUpdate();
      GameManager::PostUpdate();
      Scene��Children��PostUpdate();
    <���U���g��ʃ��[�v����/>
    !--���U���g��ʃ��[�v��������GameManager::GameEnd(Scene*);���Ă΂ꂽ��
    <�����Ŏw�肵��Scene�ւ�(��Scene)�J�ڏ���>
      BaseGameScene::OnHide();
      BaseGameScene::OnHideFinish();
      GameManager::End();
      <���[�f�B���O��ʂōs���鏈��>
        BaseGameScene::OnUnload();
        GameManager::OnUnload();
        ��Scene::OnLoad();
        ��Scene::OnSetup();
      <���[�f�B���O��ʂōs���鏈��/>
      ��Scene::OnShow();
      ��Scene::OnShowFinish();
    <�����Ŏw�肵��Scene�ւ�(��Scene)�J�ڏ���/>

  (5)
    !--Start(GameSetting* setting)���A���łɃQ�[�����N�����Ă����ꍇ
    GameSetting
*/

/*
  �Q�[��������Scene���̏����Ɉˑ������Ȃ��B
  DebugScene�����ۂ̗��֐����l���č쐬����
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

  //�Q�[���J�n�B
  //�Q�[���ݒ��ς��ĊJ�n���Ȃ��������\�B
  void Start(GameSetting* setting);
  void GameStart();

  void PreUpdate();
  void Update();
  void PostUpdate();

  //�Q�[���̈ꎞ��~
  void GamePause();

  //�Q�[���̍ĊJ
  void GameResume();
 
  //�Q�[���I���㏈���i���U���g�Ȃǁj
  void ToResult();

  //�Q�[���I�������B
  void GameEnd(Scene* next_scene);

  //�S�Ă̏����̏I���㏈��
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
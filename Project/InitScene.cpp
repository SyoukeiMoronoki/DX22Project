#include "InitScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameDirector.h"

InitScene::InitScene()
{
}

void InitScene::OnLoad(IResourceLoadReserver* resource)
{
}

void InitScene::OnSetup()
{
}

void InitScene::OnUnload()
{
}

void InitScene::OnShow(ISceneShowListener* listener)
{
}

void InitScene::OnHide(ISceneHideListener* listener)
{
}

void InitScene::Update()
{
  //�Q�[���̐ݒ�
  //PlayerEntryListBuilder��
  //�v���C���[�̎Q���󋵂̐ݒ肩��ǂ̂悤�Ƀv���C���[���쐬���邩�̃N���X
  //�������܂肢���݌v�ł͂Ȃ��C������B
  GameSetting* setting = new GameSetting();
  //GameSetting* setting = new GameSetting(new PlayerEntryListBuilder_MultiTest()); //�R���s���[�^�[���J�����\������郂�[�h

  //�Q�[���̃��x���f�U�C���ׂ̈̐��l
  //�X�e�[�W�̍L����A�S�L�����N�^�[�̃X�e�[�^�X�ɂ�����d�݂Ȃǂ𒲐��ł���
  GameLevelParam& param = setting->GetLevelParam();
  param.world_radius = 495.0f;

  //��蕨�̃X�e�[�^�X�ɂ�����d��
  param.accel_weight = 0.005f;
  param.speed_weight = 0.0075f;
  param.rot_speed_weight = 0.0002f;
  param.power_weight = 0.01f;

  //param.star_levels.star_count = 100;
    
  //�����̐ݒ�����߂�ߒ����v���O�������ōs���Ă��邪�A
  //���ۂɂ̓Q�[���J�n�܂łɎ����ʂŃv���C���[����������x�ݒ�ł���悤�ɂ���Ƃ���
  //�i�v���C���[��b�o�t�̐l���A�X�e�[�W�̍L���Ȃǁj

  //���s����V�[���A�L�����N�^�[�̎Q���󋵁A�Q�[���̐ݒ��GameDirector�ɓn���A�Q�[���J�n
  //GameDirector::GameStart(new GameScene(), setting);
  Director::GetInstance()->ChangeScene(new TitleScene());
}

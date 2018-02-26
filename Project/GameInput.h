#pragma once

#include <HalEngine.h>

//GameInput
//�Q�[���̓��͂��`����
namespace GameInput
{

//�V�����{�^�����͂��`���������͂��̗񋓌^�ɒǉ����Ă���
//�ǉ������ꍇ�Acpp�t�@�C�����Ƀ{�^���̏ڍׂ��`���Ă���
enum Kind
{
  X_AXIS, //X������
  Y_AXIS, //Y������
  SCREEN_X, //X����ʏ�ʒu
  SCREEN_Y, //Y����ʏ�ʒu
  FOCUS,  //���_�����킹��
  FIRE,   //�V���b�g
  EYE,    //��
  SCOPE,  //�X�R�[�v

  GAME_INPUT_DATANUM, //�����͐G��Ȃ�
};

//�����͐G��Ȃ�
const InputEntity* GetInputEntities();

}
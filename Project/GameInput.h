#pragma once

#include <HalEngine.h>

//GameInput
//�Q�[���̓��͂��`����
namespace GameInput
{

//�V�����{�^�����͂��`���������͂��̗񋓌^�ɒǉ����Ă���
//�ǉ������ꍇ�Acpp�t�@�C�����Ƀ{�^���̏ڍׂ��`���Ă���
enum
{
  X_AXIS, //X������
  Y_AXIS, //Y������
  L1,     //L1
  R1,     //R1
  L2,     //L2
  R2,     //R2
  FIRE,   //�V���b�g



  GAME_INPUT_DATANUM, //�����͐G��Ȃ�
};

//�����͐G��Ȃ�
const InputEntity* GetInputEntities();

}
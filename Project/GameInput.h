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
  FIRE,   //�V���b�g
  EYE,    //��

  GAME_INPUT_DATANUM, //�����͐G��Ȃ�
};

//�����͐G��Ȃ�
const InputEntity* GetInputEntities();

}
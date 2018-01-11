#include "GameInput.h"

using namespace EngineInput;

//�{�^���̏ڍאݒ���s��
//InputEntity�̃R���X�g���N�^�𕡐���`���Ă���̂ŁA�ŏ����̐ݒ�Ń{�^���̒�`���s����
//
//�R���X�g���N�^���̂P�@�\���Ȃ����̓^�C�v
// uint8        id                 GameInput.h�Œ�`����ID
// Digital::ID  negative_button    �}�C�i�X�����̃{�^������ID
// Digital::ID  positive_button    �v���X�����̃{�^������ID
// Analog::ID   axis               �A�i���O����ID
// uint8        dimention          �A�i���O���͎��ix = 0, y = 1�j
//
//�R���X�g���N�^���̂Q�@�{�^���̂݃^�C�v
// uint8        id                 GameInput.h�Œ�`����ID
// Digital::ID  button             �{�^��ID
//
//�R���X�g���N�^���̂R�@�A�i���O�̂݃^�C�v
// uint8        id                 GameInput.h�Œ�`����ID
// Analog::ID   axis               �A�i���O����ID
// uint8        dimention          �A�i���O���͎��ix = 0, y = 1�j
//

static const InputEntity INPUT_ENTITIES[GameInput::GAME_INPUT_DATANUM] =
{
  { GameInput::X_AXIS, Digital::ID_LEFT, Digital::ID_RIGHT, Analog::ID_L_0_XY, Analog::DIMENSION_X },
  { GameInput::Y_AXIS, Digital::ID_DOWN, Digital::ID_UP, Analog::ID_L_0_XY, Analog::DIMENSION_Y },
  { GameInput::SCREEN_X, Analog::ID_SCREEN_0_XY, Analog::DIMENSION_X },
  { GameInput::SCREEN_Y, Analog::ID_SCREEN_0_XY, Analog::DIMENSION_Y },
  { GameInput::FIRE, Digital::ID_X },
  { GameInput::EYE, Digital::ID_Y },
};

//�����͐G��Ȃ�
const InputEntity* GameInput::GetInputEntities()
{
  return INPUT_ENTITIES;
}

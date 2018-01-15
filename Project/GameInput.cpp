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
  { GameInput::X_AXIS, Digital::ID_LEFT2, Digital::ID_RIGHT2, Analog::ID_L_0_XY, Analog::DIMENSION_X },
  { GameInput::Y_AXIS, Digital::ID_DOWN2, Digital::ID_UP2, Analog::ID_L_0_XY, Analog::DIMENSION_Y },
  { GameInput::SCREEN_X, Digital::ID_LEFT3, Digital::ID_RIGHT3, Analog::ID_R_0_XY, Analog::DIMENSION_X },
  { GameInput::SCREEN_Y, Digital::ID_DOWN3, Digital::ID_UP3, Analog::ID_R_0_XY, Analog::DIMENSION_Y },
  { GameInput::FOCUS, Digital::ID_L1 },
  { GameInput::FIRE, Digital::ID_X },
  { GameInput::EYE, Digital::ID_Y },
  { GameInput::SCOPE, Digital::ID_A },
};

//�����͐G��Ȃ�
const InputEntity* GameInput::GetInputEntities()
{
  return INPUT_ENTITIES;
}

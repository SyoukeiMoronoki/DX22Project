#include "GameInput.h"

using namespace EngineInput;

//ボタンの詳細設定を行う
//InputEntityのコンストラクタを複数定義しているので、最小限の設定でボタンの定義が行える
//
//コンストラクタその１　予備なし入力タイプ
// uint8        id                 GameInput.hで定義したID
// Digital::ID  negative_button    マイナス方向のボタン入力ID
// Digital::ID  positive_button    プラス方向のボタン入力ID
// Analog::ID   axis               アナログ入力ID
// uint8        dimention          アナログ入力軸（x = 0, y = 1）
//
//コンストラクタその２　ボタンのみタイプ
// uint8        id                 GameInput.hで定義したID
// Digital::ID  button             ボタンID
//
//コンストラクタその３　アナログのみタイプ
// uint8        id                 GameInput.hで定義したID
// Analog::ID   axis               アナログ入力ID
// uint8        dimention          アナログ入力軸（x = 0, y = 1）
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

//ここは触らない
const InputEntity* GameInput::GetInputEntities()
{
  return INPUT_ENTITIES;
}

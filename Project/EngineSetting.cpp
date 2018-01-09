#include "EngineSetting.h"

#include "InitScene.h"

#include "GameDirector.h"
#include "GameInput.h"

void EngineSetting::OnGameInit()
{
}

void EngineSetting::OnGameFinal()
{
}

void EngineSetting::InputSetting(InputSettingBuilder* setting)
{
  setting->SetPlayerCount(4);
  setting->Register(GameInput::GetInputEntities(), GameInput::GAME_INPUT_DATANUM);
}

Scene* EngineSetting::FirstScene()
{
  return new InitScene();
}

TSize EngineSetting::WinodwSize()
{
  return TSize(1366, 768);
}

const char* EngineSetting::ActivityName()
{
  return "Test";
}

T_UINT16 EngineSetting::RenderCycle()
{
  return 1000 / 60;
}

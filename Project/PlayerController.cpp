#include "PlayerController.h"
#include <algorithm>

#include "Player.h"
#include "GameInput.h"

PlayerController::PlayerController(T_UINT8 id)
  : id_(id)
{}

void PlayerController::InputProcess(PlayerInput* dest)
{
  using namespace HalEngine;
  InputState* input = Input(this->id_);
  T_FLOAT x = input->GetAxis(GameInput::X_AXIS, 0.2f);
  T_FLOAT y = input->GetAxis(GameInput::Y_AXIS, 0.2f);
  T_FLOAT z = input->GetAxis(GameInput::R2, 0.2f) - input->GetAxis(GameInput::L2, 0.2f);
  dest->SetVectorInput(x, y, z);

  PlayerInput::CommandKind command = PlayerInput::PLAYER_COMMAND_NONE;
  if (input->GetButton(GameInput::FIRE))
  {
    command = PlayerInput::PLAYER_COMMAND_SHOT;
  }
  dest->SetCommandInput(command);
}

T_UINT8 PlayerController::GetID()
{
  return this->id_;
}

bool PlayerController::IsComputer()
{
  return false;
}

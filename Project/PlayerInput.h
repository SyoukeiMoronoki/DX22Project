#pragma once

#include <HalEngine.h>

class PlayerInput
{
public:
  enum CommandKind
  {
    PLAYER_COMMAND_SHOT,
    PLAYER_COMMAND_DATANUM,

    PLAYER_COMMAND_NONE,
  };
public:
  PlayerInput()
    : vector_input_()
    , command_input_(PLAYER_COMMAND_NONE)
  {}

public:
  inline void SetVectorInput(const TVec3f& input)
  {
    this->vector_input_ = input;
  }
  inline void SetVectorInput(T_FLOAT x, T_FLOAT y, T_FLOAT z)
  {
    this->vector_input_.x = x;
    this->vector_input_.y = y;
    this->vector_input_.z = z;
  }
  inline const TVec3f& GetVectorInput() const
  {
    return this->vector_input_;
  }
  inline void SetCommandInput(CommandKind command)
  {
    this->command_input_ = command;
  }
  inline CommandKind GetCommandInput() const
  {
    return this->command_input_;
  }
private:
  TVec3f vector_input_;
  CommandKind command_input_;
};

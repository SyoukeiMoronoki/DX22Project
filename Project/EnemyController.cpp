#include "EnemyController.h"
#include <stdlib.h>
#include <math.h>

EnemyController::EnemyController(T_UINT8 id)
  : id_(id)
{}

void EnemyController::InputProcess(PlayerInput* dest)
{
  T_FLOAT rad = (T_FLOAT)(((T_DOUBLE)rand() / RAND_MAX + 1) * MathConstants::PI * 2.0f);
  T_FLOAT x = cosf(rad);
  T_FLOAT y = sinf(rad);
  dest->SetVectorInput(x, y, 0.0f);
}

T_UINT8 EnemyController::GetID()
{
  return this->id_;
}

bool EnemyController::IsComputer()
{
  return true;
}

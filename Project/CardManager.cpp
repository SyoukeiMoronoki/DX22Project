#include "CardManager.h"
#include "CardFacade.h"

CardManager::CardManager()
{
  for (T_UINT8 i = 0; i < PlayerInput::PLAYER_COMMAND_DATANUM; ++i)
  {
    this->cards_[i] = nullptr;
  }
}

CardManager::~CardManager()
{
}

void CardManager::SetCard(T_UINT8 command, Card* card)
{
  this->cards_[command] = card;
}

Card* CardManager::GetCard(T_UINT8 command)
{
  return this->cards_[command];
}

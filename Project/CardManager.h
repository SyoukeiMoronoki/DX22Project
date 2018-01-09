#pragma once

#include <HalEngine.h>

#include "PlayerInput.h"
#include "Card.h"

class CardFacade;

class CardManager
{
public:
  CardManager();
  ~CardManager();

public:
  //セットされたカードの解放は行いません
  void SetCard(T_UINT8 command, Card* card);
  Card* GetCard(T_UINT8 command);
  
private:
  Card* cards_[PlayerInput::PLAYER_COMMAND_DATANUM];
};
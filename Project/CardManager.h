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
  //�Z�b�g���ꂽ�J�[�h�̉���͍s���܂���
  void SetCard(T_UINT8 command, Card* card);
  Card* GetCard(T_UINT8 command);
  
private:
  Card* cards_[PlayerInput::PLAYER_COMMAND_DATANUM];
};
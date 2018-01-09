#include "CardFactory.h"

#include "CardAttribute_Bomb.h"
#include "CardAttribute_Booster.h"
#include "CardAttribute_Trap.h"

namespace CardFactory
{

static const T_FLOAT BOOSTER_DEFAULT_SPEED = 17.5f;
static const T_UINT8 BOOSTER_DEFAULT_DELAY = 50;

static const T_FLOAT TRAP_DEFAULT_THROW_LENGTH = 256.0f;
static const T_FLOAT TRAP_DEFAULT_RADIUS = 128.0f;

static const T_FLOAT BOMB_DEFAULT_THROW_LENGTH = 256.0f;
static const T_FLOAT BOMB_DEFAULT_RADIUS = 128.0f;

static const CardData CARD_DATAS[CARD_KIND_DATANUM] =
{
  { CARD_KIND_BOOSTER,          1, "�u�[�X�g", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_SP_ATUM,  3, "�A�g�D���u�[�X�g", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_EX_ATUM,  7, "�A�g�D��EX�u�[�X�g", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_SP_THOTH, 3, "�g�[�g�u�[�X�g", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_EX_THOTH, 7, "�g�[�gEX�u�[�X�g", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },

  { CARD_KIND_TRAP,             1, "�g���b�v", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_SP_KHEPRI,   3, "�P�v���g���b�v", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_EX_KHEPRI,   7, "�P�v��EX�g���b�v", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_SP_ANUBIS,   3, "�A�k�r�X�g���b�v", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_EX_ANUBIS,   7, "�A�k�r�XEX�g���b�v", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },

  { CARD_KIND_BOMB,             1, "�{��", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_SP_RA,       3, "���[�{��", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_EX_RA,       7, "���[EX�{��", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_SP_SESCHAT,  3, "�Z�V���g�{��", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_EX_SESCHAT,  7, "�Z�V���gEX�{��", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },


  { CARD_KIND_AMARI,  99, "�]��", nullptr },
};

Card* CardFactory::CreateCard(CardKind kind)
{
  for (T_UINT8 i = 0; i < CARD_KIND_DATANUM; ++i)
  {
    if (kind == CARD_DATAS[i].id)
    {
      return new Card(&CARD_DATAS[i]);
    }
  }
  return nullptr;
}

}


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
  { CARD_KIND_BOOSTER,          1, "ブースト", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_SP_ATUM,  3, "アトゥムブースト", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_EX_ATUM,  7, "アトゥムEXブースト", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_SP_THOTH, 3, "トートブースト", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },
  { CARD_KIND_BOOSTER_EX_THOTH, 7, "トートEXブースト", new CardAttribute_Booster(BOOSTER_DEFAULT_SPEED, BOOSTER_DEFAULT_DELAY) },

  { CARD_KIND_TRAP,             1, "トラップ", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_SP_KHEPRI,   3, "ケプリトラップ", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_EX_KHEPRI,   7, "ケプリEXトラップ", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_SP_ANUBIS,   3, "アヌビストラップ", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },
  { CARD_KIND_TRAP_EX_ANUBIS,   7, "アヌビスEXトラップ", new CardAttribute_Trap(TRAP_DEFAULT_THROW_LENGTH, TRAP_DEFAULT_RADIUS) },

  { CARD_KIND_BOMB,             1, "ボム", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_SP_RA,       3, "ラーボム", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_EX_RA,       7, "ラーEXボム", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_SP_SESCHAT,  3, "セシャトボム", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },
  { CARD_KIND_BOMB_EX_SESCHAT,  7, "セシャトEXボム", new CardAttribute_Bomb(BOMB_DEFAULT_THROW_LENGTH, BOMB_DEFAULT_RADIUS) },


  { CARD_KIND_AMARI,  99, "余り", nullptr },
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


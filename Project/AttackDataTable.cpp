#include "AttackDataTable.h"

#include "AttackAttribute_Bomb.h"
#include "Asset.h"

static const T_UINT8 ATTACK_MAX_COUNT = 32;

static const AttackData ATTACK_DATAS[AttackDataTable::ATTACK_KIND_DATANUM] =
{
  { AttackDataTable::ATTACK_KIND_BOMB, "ƒ{ƒ€", 35, Asset::Texture::STAR, new AttackAttribute_Bomb(28.0f, 512.0f) },
};

const AttackData* AttackDataTable::GetAttackData(AttackKind kind)
{
  for (T_UINT8 i = 0; i < AttackDataTable::ATTACK_KIND_DATANUM; ++i)
  {
    if (ATTACK_DATAS[i].id == kind)
    {
      return &ATTACK_DATAS[i];
    }
  }
  return nullptr;
}

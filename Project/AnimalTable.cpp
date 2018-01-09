#include "AnimalTable.h"

namespace AnimalTable
{

static const AnimalData ERROR = { T_UINT8_MAX, "�G���[", "���̃��b�Z�[�W�� �݂��̂� ����������" };

static const AnimalData ANIMAL_DATAS[ANIMAL_ID_DATANUM] =
{
  { ANIMAL_ID_TEST, "�e�X�g", "����񃏃�" },
};

const AnimalData& GetAnimalData(T_UINT8 id)
{
  for (T_UINT8 i = 0; i < ANIMAL_ID_DATANUM; ++i)
  {
    if (ANIMAL_DATAS[i].id == id)
    {
      return ANIMAL_DATAS[i];
    }
  }
  return ERROR;
}

}
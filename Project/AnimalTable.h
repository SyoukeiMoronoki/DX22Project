#pragma once

#include "AnimalData.h"

/*
  ���CSV�f�[�^����ǂݎ������ɕύX����
*/

namespace AnimalTable
{

enum AnimalID
{
  ANIMAL_ID_TEST,

  ANIMAL_ID_DATANUM,
};

const AnimalData& GetAnimalData(T_UINT8 id);

}
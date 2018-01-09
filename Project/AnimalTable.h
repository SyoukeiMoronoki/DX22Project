#pragma once

#include "AnimalData.h"

/*
  後にCSVデータから読み取る方式に変更する
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
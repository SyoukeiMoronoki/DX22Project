#include "GachaTable.h"
#include "VehicleTable.h"

enum { GACHA_DATA_COUNT = 10 };

static const GachaData GACHA_DATAS[GACHA_DATA_COUNT] =
{
  { GachaTable::TABLE_LEVEL_ZAKO, 95, VehicleTable::VEHICLE_ID_NONE },
  { GachaTable::TABLE_LEVEL_ZAKO, 5, VehicleTable::VEHICLE_ID_CAR },

  { GachaTable::TABLE_LEVEL_YOWAI, 75, VehicleTable::VEHICLE_ID_NONE },
  { GachaTable::TABLE_LEVEL_YOWAI, 25, VehicleTable::VEHICLE_ID_CAR },

  { GachaTable::TABLE_LEVEL_NORMAL, 50, VehicleTable::VEHICLE_ID_NONE },
  { GachaTable::TABLE_LEVEL_NORMAL, 50, VehicleTable::VEHICLE_ID_CAR },

  { GachaTable::TABLE_LEVEL_TUYOI, 25, VehicleTable::VEHICLE_ID_NONE },
  { GachaTable::TABLE_LEVEL_TUYOI, 75, VehicleTable::VEHICLE_ID_CAR },

  { GachaTable::TABLE_LEVEL_GOD, 5, VehicleTable::VEHICLE_ID_NONE },
  { GachaTable::TABLE_LEVEL_GOD, 95, VehicleTable::VEHICLE_ID_CAR },
};

T_UINT8 GachaTable::GetGachaDataCount(T_UINT8 table_id)
{
  return T_UINT8();
}

const GachaData* GachaTable::GetGachaDataList(T_UINT8 table_id)
{
  return nullptr;
}

const GachaData* GachaTable::Gacha(T_UINT8 table_id)
{
  return nullptr;
}

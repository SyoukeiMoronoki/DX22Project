#pragma once

#include <map>
#include <vector>
#include "GachaData.h"

class GachaTable
{
public:
  enum TableID
  {
    TABLE_LEVEL_ZAKO,
    TABLE_LEVEL_YOWAI,
    TABLE_LEVEL_NORMAL,
    TABLE_LEVEL_TUYOI,
    TABLE_LEVEL_GOD,
  };
public:
  T_UINT8 GetGachaDataCount(T_UINT8 table_id);
  const GachaData* GetGachaDataList(T_UINT8 table_id);

  const GachaData* Gacha(T_UINT8 table_id);

private:
  std::map<T_UINT8, std::vector<GachaData>> gacha_tables_;

};
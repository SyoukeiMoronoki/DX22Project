#pragma once

#include "PlayerEntryDataModelList.h"
#include "PlayerEntry.h"

class IPlayerEntryListBuilder
{
public:
  virtual void Build(PlayerEntryDataModelList* models, std::vector<PlayerEntry*>* dest) = 0;
};
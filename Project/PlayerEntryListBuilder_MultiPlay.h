#pragma once

#include "IPlayerEntryListBuilder.h"

class PlayerEntryListBuilder_MultiPlay : public IPlayerEntryListBuilder
{
public:
  virtual void Build(PlayerEntryDataModelList* models, std::vector<PlayerEntry*>* dest) override;
};
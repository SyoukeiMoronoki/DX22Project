#include "PlayerEntryDataModel.h"


#include "AnimalTable.h"


PlayerEntryDataModel::PlayerEntryDataModel(T_UINT8 id)
  : id_(id)
{
}

PlayerEntryDataModel::~PlayerEntryDataModel()
{
}

void PlayerEntryDataModel::Reset()
{
}

void PlayerEntryDataModel::AddListener(IPlayerEntryBuilderListener* listener)
{
  this->listeners_.push_back(listener);
}

void PlayerEntryDataModel::RemoveListener(IPlayerEntryBuilderListener* listener)
{
  this->listeners_.remove(listener);
}

void PlayerEntryDataModel::ClearListener()
{
  this->listeners_.clear();
}

void PlayerEntryDataModel::OnChangeId()
{
}

void PlayerEntryDataModel::OnChangeAnimalId()
{
}

void PlayerEntryDataModel::OnChangeEntryKind()
{
}

void PlayerEntryDataModel::OnChangeHandicap()
{
}

void PlayerEntryDataModel::OnChangeLevel()
{
}

void PlayerEntryDataModel::SetAnimalData(const AnimalData& data)
{
  this->animal_data_ = &data;
  this->OnChangeId();
}

void PlayerEntryDataModel::SetEntryKind(T_UINT8 entry_kind)
{
  this->entry_kind_ = entry_kind;
  this->OnChangeEntryKind();
}

void PlayerEntryDataModel::SetHandicap(T_UINT8 handicap)
{
  this->handicap_ = handicap;
  this->OnChangeHandicap();
}

void PlayerEntryDataModel::SetLevel(T_UINT8 level)
{
  this->level_ = level;
  this->OnChangeLevel();
}

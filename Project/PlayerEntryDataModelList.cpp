#include "PlayerEntryDataModelList.h"

#include "PlayerController.h"
#include "EnemyController.h"

PlayerEntryDataModelList::PlayerEntryDataModelList(T_UINT8 entries_count)
  : entries_count_(entries_count)
{
  this->entries_ = new PlayerEntryDataModel*[this->entries_count_];
  for (T_UINT8 i = 0; i < this->entries_count_; ++i)
  {
    this->entries_[i] = new PlayerEntryDataModel(i);
  }
}

PlayerEntryDataModelList::~PlayerEntryDataModelList()
{
  for (T_UINT8 i = 0; i < this->entries_count_; ++i)
  {
    delete this->entries_[i];
  }
  delete[] this->entries_;
}

PlayerEntryDataModel* PlayerEntryDataModelList::AddEntry(PlayerEntryDataModel::PlayerEntryKind kind)
{
  PlayerEntryDataModel* new_entry = GetEmptyEntry();
  if (!new_entry)
  {
    return nullptr;
  }
  new_entry->SetEntryKind(kind);
  return new_entry;
}

void PlayerEntryDataModelList::SetEntry(T_UINT8 id, T_UINT8 kind)
{
  this->entries_[id]->SetEntryKind(kind);
}

void PlayerEntryDataModelList::IncrementEntryKind(T_UINT8 id)
{
  const T_UINT8 kind = (this->entries_[id]->GetEntryKind() + 1) % PlayerEntryDataModel::PLAYER_ENTRY_DATANUM;
  this->entries_[id]->SetEntryKind(kind);
}

void PlayerEntryDataModelList::ResetEntry(T_UINT8 id)
{
  this->entries_[id]->SetEntryKind(PlayerEntryDataModel::PLAYER_ENTRY_NONE);
}

void PlayerEntryDataModelList::ResetEntries()
{
  for (T_UINT8 i = 0; i < this->entries_count_; ++i)
  {
    this->entries_[i]->Reset();
  }
}

PlayerEntryDataModel* PlayerEntryDataModelList::GetEmptyEntry()
{
  for (T_UINT8 i = 0; i < this->entries_count_; ++i)
  {
    if (this->entries_[i]->GetEntryKind() == PlayerEntryDataModel::PLAYER_ENTRY_NONE)
    {
      return this->entries_[i];
    }
  }
  return nullptr;
}

#pragma once

#include <vector>
#include "PlayerEntryDataModel.h"

/*
  �v���C���[�̎Q���󋵂�ݒ肷��N���X
  �v���C���[�Z���N�g��ʂŗ��p���鎖���ł���
*/

class PlayerEntryDataModelList
{
public:
  PlayerEntryDataModelList(T_UINT8 entries_count);
  ~PlayerEntryDataModelList();

public:
  PlayerEntryDataModel* AddEntry(PlayerEntryDataModel::PlayerEntryKind kind);

  void SetEntry(T_UINT8 id, T_UINT8 kind);
  //�w��h�c�̃v���C���[�̎Q����Ԃ�؂�ւ�
  //�i�v���C���[���R���s���[�^�[���s�Q�����v���C���[���c�Ń��[�v�j
  void IncrementEntryKind(T_UINT8 id);
  //�w��h�c�̃v���C���[�𖢎Q����
  void ResetEntry(T_UINT8 id);

  void ResetEntries();

protected:
  PlayerEntryDataModel* GetEmptyEntry();

public:
  inline PlayerEntryDataModel* GetEntry(T_UINT8 id) const
  {
    return this->entries_[id];
  }

  inline T_UINT8 GetEntriesCount() const
  {
    return this->entries_count_;
  }

private:
  //PlayerEntryDataModel���g�������Ă���id�Ɣz���id�͑Ή����Ă���
  const T_UINT8 entries_count_;
  PlayerEntryDataModel** entries_;
};

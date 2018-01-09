#pragma once

#include <list>
#include "AnimalData.h"

/*
  PlayerEntryのデータモデルクラス
  プレイヤーセレクト画面で利用する為のリスナーを用意してある

  MVCパターンでのModelにあたる部分
*/

class PlayerEntryDataModel;

class IPlayerEntryBuilderListener
{
public:
  virtual void OnAttached(const PlayerEntryDataModel& builder) = 0;

  virtual void OnChangeId(const PlayerEntryDataModel& builder) = 0;
  virtual void OnChangeAnimalId(const PlayerEntryDataModel& builder) = 0;
  virtual void OnChangeEntryKind(const PlayerEntryDataModel& builder) = 0;
  virtual void OnChangeHandicap(const PlayerEntryDataModel& builder) = 0;
  virtual void OnChangeLevel(const PlayerEntryDataModel& builder) = 0;
};

class PlayerEntryDataModel
{
public:
  enum PlayerEntryKind
  {
    PLAYER_ENTRY_NONE,
    PLAYER_ENTRY_PLAYER,
    PLAYER_ENTRY_COMPUTER,

    PLAYER_ENTRY_DATANUM,
  };

public:
  PlayerEntryDataModel(T_UINT8 id);
  ~PlayerEntryDataModel();

public:
  void Reset();

public:
  //Listenerのインスタンスの解放は行わない
  void AddListener(IPlayerEntryBuilderListener* listener);
  void RemoveListener(IPlayerEntryBuilderListener* listener);
  void ClearListener();

  void OnChangeId();
  void OnChangeAnimalId();
  void OnChangeEntryKind();
  void OnChangeHandicap();
  void OnChangeLevel();

public:
  inline T_UINT8 GetId() const
  {
    return this->id_;
  }

  void SetAnimalData(const AnimalData& data);
  inline const AnimalData& GetAnimalData() const
  {
    return *this->animal_data_;
  }

  void SetEntryKind(T_UINT8 entry_kind);
  inline T_UINT8 GetEntryKind() const
  {
    return this->entry_kind_;
  }

  void SetHandicap(T_UINT8 handicap);
  inline T_UINT8 GetHandicap() const
  {
    return this->entry_kind_;
  }

  void SetLevel(T_UINT8 level);
  inline T_UINT8 GetLevel() const
  {
    return this->level_;
  }

private:
  T_UINT8 id_;
  const AnimalData* animal_data_;
  T_UINT8 entry_kind_;
  T_UINT8 handicap_;
  //
  T_UINT8 level_;

  std::list<IPlayerEntryBuilderListener*> listeners_;
};
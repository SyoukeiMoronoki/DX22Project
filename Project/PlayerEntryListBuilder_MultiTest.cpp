#include "PlayerEntryListBuilder_MultiTest.h"

#include <vector>

#include "PlayerController.h"
#include "EnemyController.h"
#include "PlayerCamera.h"
#include "ComputerCamera.h"

struct PlayerCameraViewport
{
  T_FLOAT x;
  T_FLOAT y;
  T_FLOAT width;
  T_FLOAT height;
};

static void CreatePlayerCameraViewport(T_UINT8 player_count, std::vector<PlayerCameraViewport>* viewport_list)
{
  T_UINT8 x_num = 0;
  T_UINT8 y_num = 0;
  if (player_count == 1)
  {
    x_num = 1;
    y_num = 1;
  }
  else if (player_count == 2)
  {
    x_num = 2;
    y_num = 1;
  }
  else if (player_count <= 4)
  {
    x_num = 2;
    y_num = 2;
  }
  else if (player_count <= 6)
  {
    x_num = 3;
    y_num = 2;
  }
  else if (player_count <= 9)
  {
    x_num = 3;
    y_num = 3;
  }
  else
  {
    //ëŒâûÇ∑ÇÈà”ñ°Ç†ÇÈÇÃÇ©
  }

  PlayerCameraViewport viewport;
  viewport.width = (T_FLOAT)Director::GetInstance()->GetScreenWidth() / x_num;
  viewport.height = (T_FLOAT)Director::GetInstance()->GetScreenHeight() / y_num;
  for (T_UINT8 id = 0; id < player_count; ++id)
  {
    const T_UINT8 x = id % x_num;
    const T_UINT8 y = id / x_num;
    viewport.x = viewport.width * x;
    viewport.y = viewport.height * y;
    viewport_list->push_back(viewport);
  }
}

static PlayerEntry* BuildPlayerEntry(PlayerEntryDataModel* model, T_UINT8* player_id, T_UINT8* computer_id, const std::vector<PlayerCameraViewport>& viewport_list)
{
  T_UINT8 kind = model->GetEntryKind();
  if (kind == PlayerEntryDataModel::PLAYER_ENTRY_NONE)
  {
    return nullptr;
  }
  const PlayerCameraViewport& viewport = viewport_list[*player_id + *computer_id];
  IPlayerController* controller = nullptr;
  IPlayerCamera* camera = new PlayerCamera(viewport.x, viewport.y, viewport.width, viewport.height);
  if (kind == PlayerEntryDataModel::PLAYER_ENTRY_PLAYER)
  {
    controller = new PlayerController(*player_id);
    (*player_id)++;
  }
  if (kind == PlayerEntryDataModel::PLAYER_ENTRY_COMPUTER)
  {
    //TODO:ÉåÉxÉãê›íËÇ™îΩâfÇ≥ÇÍÇÈÇÊÇ§Ç…
    controller = new EnemyController(*computer_id);
    (*computer_id)++;
  }
  return new PlayerEntry(
    *model,
    controller,
    camera
  );
}

void PlayerEntryListBuilder_MultiTest::Build(PlayerEntryDataModelList* models, std::vector<PlayerEntry*>* dest)
{
  T_UINT8 entries_count = models->GetEntriesCount();
  T_UINT8 player_id = 0;
  T_UINT8 computer_id = 0;
  T_UINT8 player_count = 0;
  for (T_UINT8 i = 0; i < entries_count; ++i)
  {
    PlayerEntryDataModel* const model = models->GetEntry(i);
    if (model->GetEntryKind() != PlayerEntryDataModel::PLAYER_ENTRY_NONE)
    {
      player_count++;
    }
  }
  std::vector<PlayerCameraViewport> viewport_list = std::vector<PlayerCameraViewport>();
  CreatePlayerCameraViewport(player_count, &viewport_list);
  for (T_UINT8 i = 0; i < entries_count; ++i)
  {
    PlayerEntryDataModel* const model = models->GetEntry(i);
    PlayerEntry* entry = BuildPlayerEntry(model, &player_id, &computer_id, viewport_list);
    if (!entry)
    {
      continue;
    }
    dest->push_back(entry);
  }
}

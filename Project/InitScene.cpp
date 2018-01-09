#include "InitScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameDirector.h"
#include "PlayerEntryDataModelList.h"
#include "PlayerEntryListBuilder_MultiPlay.h"
#include "PlayerEntryListBuilder_MultiTest.h"

InitScene::InitScene()
{
}

void InitScene::OnLoad(IResourceLoadReserver* resource)
{
}

void InitScene::OnSetup()
{
}

void InitScene::OnUnload()
{
}

void InitScene::OnShow(ISceneShowListener* listener)
{
}

void InitScene::OnHide(ISceneHideListener* listener)
{
}

void InitScene::Update()
{
  //ゲームの設定
  //PlayerEntryListBuilderは
  //プレイヤーの参加状況の設定からどのようにプレイヤーを作成するかのクラス
  //正直あまりいい設計ではない気もする。
  //GameSetting* setting = new GameSetting(new PlayerEntryListBuilder_MultiPlay());
  GameSetting* setting = new GameSetting(new PlayerEntryListBuilder_MultiTest()); //コンピューターもカメラ表示されるモード

  //ゲームのレベルデザインの為の数値
  //ステージの広さや、全キャラクターのステータスにかかる重みなどを調整できる
  GameLevelParam& param = setting->GetLevelParam();
  param.world_radius = 495.0f;

  //乗り物のステータスにかかる重み
  param.accel_weight = 0.005f;
  param.speed_weight = 0.0075f;
  param.rot_speed_weight = 0.0002f;
  param.power_weight = 0.01f;

  //星生成にまつわるパラメータ
  param.star_levels.star_count = 36;
  param.star_levels.star_lifetime = 100;
  param.star_levels.star_scale_min = 50.0f;
  param.star_levels.star_scale_max = 150.0f;
  param.star_levels.star_spawn_delay = 1;
  param.star_levels.star_spawn_radius = 490.0f;
  //param.star_levels.star_count = 100;

  //プレイヤーの参加状況を決める
  //計9人まで対応(意味無し)
  static const T_UINT8 PLAYER_COUNT = 1;
  static const T_UINT8 COMPUTER_COUNT = 8;
  PlayerEntryDataModelList* entries = new PlayerEntryDataModelList(PLAYER_COUNT + COMPUTER_COUNT);
  for (T_UINT8 i = 0; i < PLAYER_COUNT; ++i)
  {
    entries->AddEntry(PlayerEntryDataModel::PLAYER_ENTRY_PLAYER);
  }
  for (T_UINT8 i = 0; i < COMPUTER_COUNT; ++i)
  {
    entries->AddEntry(PlayerEntryDataModel::PLAYER_ENTRY_COMPUTER);
  }
  
  //これらの設定を決める過程をプログラム内で行っているが、
  //実際にはゲーム開始までに至る画面でプレイヤー側がある程度設定できるようにするといい
  //（プレイヤーやＣＰＵの人数、ステージの広さなど）

  //実行するシーン、キャラクターの参加状況、ゲームの設定をGameDirectorに渡し、ゲーム開始
  GameDirector::GameStart(new GameScene(), entries, setting);
}

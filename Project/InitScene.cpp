#include "InitScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameDirector.h"

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
  GameSetting* setting = new GameSetting();
  //GameSetting* setting = new GameSetting(new PlayerEntryListBuilder_MultiTest()); //コンピューターもカメラ表示されるモード

  //ゲームのレベルデザインの為の数値
  //ステージの広さや、全キャラクターのステータスにかかる重みなどを調整できる
  GameLevelParam& param = setting->GetLevelParam();
  param.world_radius = 495.0f;

  //乗り物のステータスにかかる重み
  param.accel_weight = 0.005f;
  param.speed_weight = 0.0075f;
  param.rot_speed_weight = 0.0002f;
  param.power_weight = 0.01f;

  //param.star_levels.star_count = 100;
    
  //これらの設定を決める過程をプログラム内で行っているが、
  //実際にはゲーム開始までに至る画面でプレイヤー側がある程度設定できるようにするといい
  //（プレイヤーやＣＰＵの人数、ステージの広さなど）

  //実行するシーン、キャラクターの参加状況、ゲームの設定をGameDirectorに渡し、ゲーム開始
  //GameDirector::GameStart(new GameScene(), setting);
  Director::GetInstance()->ChangeScene(new TitleScene());
}

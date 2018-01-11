#include "GameScene.h"
#include <stdlib.h>
#include "EngineSetting.h"

#include "GameSceneDirector.h"

#include "Player.h"
#include "EnemyManager.h"

#include "UI_Player.h"
#include "GameConstants.h"

#include "Asset.h"
#include "ResultScene.h"

enum ENTITY_ZINDEXES
{
  ZINDEX_BG,
  ZINDEX_ATTACK,
  ZINDEX_CURSOL,
  ZINDEX_BOYA,
  ZINDEX_UI,
};

static const T_UINT16 ENEMY_MAX = 12;
static const T_UINT16 ENEMY_SPWAN_PROBABILITY = 64;

static const T_FLOAT NEAR = 128.0f;
static const T_FLOAT FAR = 1024.0f;
static const T_FLOAT VIEWING_ANGLE = MathConstants::PI_2 / 3.0f;

static const T_UINT16 COLLIDER_CIRCLE_COUNT = 32;
static const T_UINT16 COLLIDER_RECT_COUNT = 32;

static const T_UINT8 GRAND_SLAM_ATTACK = 10;

static const T_UINT8 WEAK_HAPPY = 10;

static const T_UINT8 DAMAGE_EFFECT_TIME = 30;

static const T_UINT8 TIME_UP_SHOW_TIME = 120;

GameScene::GameScene()
{}

void GameScene::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Texture::ENEMY_WEAK_POINT);
  resource->ReserveLoad(Asset::Texture::ENEMY_ZAKO1);
  resource->ReserveLoad(Asset::Texture::ENEMY_ZAKO2);
  resource->ReserveLoad(Asset::Texture::FIELD_BG);
  resource->ReserveLoad(Asset::Texture::FIELD_BG_SONAR);
  resource->ReserveLoad(Asset::Texture::FIELD_BOYA);
  resource->ReserveLoad(Asset::Texture::FONT_NUMBER);
  resource->ReserveLoad(Asset::Texture::PLAYER_BULLET);
  resource->ReserveLoad(Asset::Texture::PLAYER_TURGET);
  resource->ReserveLoad(Asset::Texture::TEXT_HP);
  resource->ReserveLoad(Asset::Texture::TEXT_SCORE);
  resource->ReserveLoad(Asset::Texture::TEXT_SONAR);
  resource->ReserveLoad(Asset::Texture::TEXT_TIME);
  resource->ReserveLoad(Asset::Texture::TEXT_TIMEUP);
  resource->ReserveLoad(Asset::Texture::UI_EARGAUGE);
  resource->ReserveLoad(Asset::Texture::UI_HPGAUGE);
}

void GameScene::OnSetup()
{
  this->camera2d_ = new Camera2D();
  this->camera2d_->SetViewportClear(false);
  this->camera2d_->GetRenderState()->AddTargetLayerId(0);
  this->AddCamera(this->camera2d_);

  this->field_ = new MeshField(2000.0f, 2000.0f, 10, 10);
  this->field_->SetLightingEnabled(false);
  this->field_->SetTexture(Asset::Texture::FIELD_BG);
  this->field_->GetTransform()->SetY(-1.25f);
  this->field_->GetTransform()->GetRotator()->SetEularX(MathConstants::DegToRad(90.0f));
  this->AddChild(this->field_);

  this->player_ = new Player();
  this->AddChild(this->player_);

  this->enemy_manager_ = new EnemyManager(ENEMY_MAX);
  this->enemy_manager_->AttachToEntity(this->GetRoot3d());

  const TSize screen_size = Director::GetInstance()->GetScreenSize();
  this->boya_ = Sprite::CreateWithTexture(&Asset::Texture::FIELD_BOYA);
  const T_FLOAT boya_width = (T_FLOAT)this->boya_->GetTextureRegion()->GetTexture()->GetWidth();
  this->boya_->GetTransform()->SetScale(screen_size.width / boya_width, screen_size.height / boya_width);
  this->boya_->SetZIndex(ZINDEX_BOYA);

  this->ui_cursol_ = new UI_Cursol();
  this->ui_cursol_->SetZIndex(ZINDEX_CURSOL);

  this->ui_player_ = new UI_Player();
  this->ui_player_->SetZIndex(ZINDEX_UI);

  this->player_->SetView(this->ui_player_, this->ui_cursol_);

  this->text_time_up_ = Sprite::CreateWithTexture(&Asset::Texture::TEXT_TIMEUP);
  this->text_time_up_->SetVisible(false);
  this->text_time_up_->SetZIndex(ZINDEX_UI);
  this->AddChild(this->text_time_up_);

  this->AddChild(this->boya_);
  this->AddChild(this->ui_cursol_);
  this->AddChild(this->ui_player_);
  GameSceneDirector::GetInstance().Init();

  this->player_->GameInit();
  this->enemy_manager_->GameInit();
  this->ui_player_->GameInit();
  this->ui_cursol_->GameInit();

  this->boya_->SetVisible(true);
  this->boya_->SetColor(0, 0, 0, 255);
  this->text_time_up_->SetVisible(false);

  this->timeup_text_show_time_ = 0;
  this->grand_slam_count_ = 0;
  this->weak_happy_count_ = 0;
  this->damage_count_ = 0;
  this->time_count_ = GameConstants::GAME_TIME;
}

void GameScene::OnUnload()
{
  if (this->player_)
  {
    delete this->player_;
  }
  if (this->enemy_manager_)
  {
    delete this->enemy_manager_;
  }
  if (this->boya_)
  {
    delete this->boya_;
  }
  if (this->ui_cursol_)
  {
    delete this->ui_cursol_;
  }
  if (this->ui_player_)
  {
    delete this->ui_player_;
  }
}

void GameScene::OnShow(ISceneShowListener* listener)
{

}

void GameScene::OnHide(ISceneHideListener* listener)
{
}

void GameScene::Update()
{
  if (this->time_count_ == 0)
  {
    this->ui_player_->GetScoreView()->Update();
    this->timeup_text_show_time_--;
    if (this->timeup_text_show_time_ == 0)
    {
      GameSceneDirector::GetInstance().AddBonus(this->player_->GetHP());
      Director::GetInstance()->ChangeScene(new ResultScene());
      return;
    }
    return;
  }
  this->time_count_--;
  if (this->time_count_ == 0)
  {
    this->text_time_up_->SetVisible(true);
    this->timeup_text_show_time_ = TIME_UP_SHOW_TIME;
  }
  this->ui_player_->GetTimeView()->SetValue(this->time_count_ / 60);
  if (this->grand_slam_count_ > 0)
  {
    this->grand_slam_count_--;
//    this->bg_->GetTransform()->SetScale(1.0f - this->grand_slam_count_ * 0.002f);
  }
  if (this->weak_happy_count_ > 0)
  {
    this->weak_happy_count_--;
    this->boya_->SetAlpha((T_UINT8)(255 * (1.0f - ((T_FLOAT)this->weak_happy_count_ / WEAK_HAPPY))));
  }
  if (this->damage_count_ > 0)
  {
    this->damage_count_--;
    const T_FLOAT damage_effect_rate = (T_FLOAT)this->damage_count_ / DAMAGE_EFFECT_TIME;
    this->boya_->SetRed((T_UINT8)(128 * damage_effect_rate));
  }
  
  bool use_ear = this->player_->IsUseEar();
  this->field_->SetVisible(!use_ear);
  this->enemy_manager_->Update(use_ear);
 
  this->ui_player_->Update();

  if (rand() % ENEMY_SPWAN_PROBABILITY == 0)
  {
    this->enemy_manager_->SpawnToRandomPosition(this->player_);
  }
  
  if (this->enemy_manager_->AttackToPlayer(this->player_))
  {
    if (this->damage_count_ == 0)
    {
      this->damage_count_ = DAMAGE_EFFECT_TIME;
    }
  }

  this->player_->AttackToEnemy(this->enemy_manager_);
  //bool fire = this->player_->ControllProcess(state);
  //if (fire)
  //{
  //  if (this->enemy_manager_->CollisionProcess(this->ui_cursol_))
  //  {
  //    this->weak_happy_count_ = WEAK_HAPPY;
  //  }
  //  else
  //  {
  //    this->grand_slam_count_ = GRAND_SLAM_ATTACK;
  //  }
  //}
}

#include "GameScene.h"
#include <stdlib.h>
#include "EngineSetting.h"

#include "GameSceneDirector.h"

#include "Player.h"
#include "EnemyManager.h"
#include "BossController.h"

#include "UI_Player.h"
#include "GameConstants.h"

#include "Asset.h"
#include "ResultScene.h"
#include "GameDirector.h"

enum ENTITY_ZINDEXES
{
  ZINDEX_BG,
  ZINDEX_ATTACK,
  ZINDEX_CURSOL,
  ZINDEX_BOYA,
  ZINDEX_UI,
};

static const T_UINT16 ENEMY_MAX = 12;
static const T_UINT16 ENEMY_SPAWN_MAX = 12;
static const T_UINT16 ENEMY_SPWAN_PROBABILITY = 128;

static const T_FLOAT NEAR = 128.0f;
static const T_FLOAT FAR = 1024.0f;
static const T_FLOAT VIEWING_ANGLE = MathConstants::PI_2 / 3.0f;

static const T_UINT16 COLLIDER_CIRCLE_COUNT = 32;
static const T_UINT16 COLLIDER_RECT_COUNT = 32;

static const T_UINT8 GRAND_SLAM_ATTACK = 10;

static const T_UINT8 WEAK_HAPPY = 10;

static const T_UINT8 DAMAGE_EFFECT_TIME = 60;

static const T_UINT8 TIME_UP_SHOW_TIME = 120;

GameScene::GameScene()
{}

void GameScene::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Texture::ENEMY_WEAK_POINT);
  resource->ReserveLoad(Asset::Texture::ENEMY_ZAKO1);
  resource->ReserveLoad(Asset::Texture::ENEMY_ZAKO2);
  resource->ReserveLoad(Asset::Texture::ENEMY_BOSS);

  resource->ReserveLoad(Asset::Texture::FIELD_GROUND);
  resource->ReserveLoad(Asset::Texture::FIELD_GROUND_NORMAL);
  resource->ReserveLoad(Asset::Texture::FIELD_BOYA);
  resource->ReserveLoad(Asset::Texture::FONT_NUMBER);
  resource->ReserveLoad(Asset::Texture::PLAYER_BULLET);
  resource->ReserveLoad(Asset::Texture::PLAYER_BULLET_EFFECT);
  resource->ReserveLoad(Asset::Texture::PLAYER_TARGET);
  resource->ReserveLoad(Asset::Texture::PLAYER_SHADOW000);
  
  resource->ReserveLoad(Asset::Texture::TEXT_HP);
  resource->ReserveLoad(Asset::Texture::TEXT_SCORE);
  resource->ReserveLoad(Asset::Texture::TEXT_SONAR);
  resource->ReserveLoad(Asset::Texture::TEXT_TIME);
  resource->ReserveLoad(Asset::Texture::TEXT_TIME_UP);
  resource->ReserveLoad(Asset::Texture::TEXT_TUTORIAL);

  resource->ReserveLoad(Asset::Texture::UI_EAR_GAUGE);
  resource->ReserveLoad(Asset::Texture::UI_HPGAUGE);
  resource->ReserveLoad(Asset::Texture::UI_KEYBOARD);

  resource->ReserveLoad(Asset::Shader::SKY);
  resource->ReserveLoad(Asset::Shader::ZENITH);
  resource->ReserveLoad(Asset::Shader::ENEMY_BODY);
  resource->ReserveLoad(Asset::Shader::GROUND);
  resource->ReserveLoad(Asset::Shader::PLAYER_BODY);
  resource->ReserveLoad(Asset::Shader::PLAYER_SHADOW);

  //resource->ReserveLoad(Asset::FBX::NEKO);
}

void GameScene::OnSetup()
{
  this->camera2d_ = new Camera2D();
  this->camera2d_->SetViewportClear(false);
  this->AddCamera(this->camera2d_);
  
  this->field_ = new Field();
  this->AddChild(this->field_);

  this->player_ = new Player();
  this->AddChild(this->player_);

  this->enemy_manager_ = new EnemyManager(ENEMY_MAX);
  this->enemy_manager_->AttachToEntity(this->GetRoot3d());
  this->enemy_manager_->GetBulletManager()->AttachToEntity(this->GetRoot3d());

  this->boss_controller_ = new BossController();
  this->boss_controller_->AttachToEntity(this->GetRoot3d());

  const TSize screen_size = Director::GetInstance()->GetScreenSize();
  this->boya_ = Sprite::CreateWithTexture(&Asset::Texture::FIELD_BOYA);
  const T_FLOAT boya_width = (T_FLOAT)this->boya_->GetMaterial()->GetMainTexture()->GetWidth();
  this->boya_->GetTransform()->SetScale(screen_size.width / boya_width, screen_size.height / boya_width);
  this->boya_->SetZIndex(ZINDEX_BOYA);

  this->ui_player_ = new UI_Player();
  this->ui_player_->SetZIndex(ZINDEX_UI);

  this->player_->SetView(this->ui_player_);

  this->text_time_up_ = Sprite::CreateWithTexture(&Asset::Texture::TEXT_TIME_UP);
  this->text_time_up_->SetVisible(false);
  this->text_time_up_->SetZIndex(ZINDEX_UI);
  this->AddChild(this->text_time_up_);

  this->AddChild(this->boya_);
  this->AddChild(this->ui_player_);

  GameSceneDirector::GetInstance().Init(this->field_, this->player_, this->boss_controller_);

  this->player_->GameInit();
  this->ui_player_->GameInit();

  this->boya_->SetVisible(true);
  this->boya_->GetMaterial()->GetDiffuse().SetColor(0.0f, 0.0f, 0.0f, 1.0f);
  this->text_time_up_->SetVisible(false);

  this->timeup_text_show_time_ = 0;
  this->grand_slam_count_ = 0;
  this->weak_happy_count_ = 0;
  this->damage_count_ = 0;

  this->time_up_flag_ = false;
  this->zako_appear_flag_ = false;
  this->boss_appear_flag_ = false;
  
  this->enemy_spawn_count_ = 0;

  this->tutorial_ = new Tutorial();
  this->tutorial_->GetTransform()->SetY(200.0f);
  this->AddChild(this->tutorial_);
}

void GameScene::OnUnload()
{
  delete this->camera2d_;

  delete this->player_;
  delete this->enemy_manager_;
  delete this->boss_controller_;

  delete this->field_;

  delete this->ui_player_;

  delete this->boya_;
  delete this->text_time_up_;

  delete this->tutorial_;

  GameDirector::GameFinish();
}

void GameScene::OnShow(ISceneShowListener* listener)
{

}

void GameScene::OnHide(ISceneHideListener* listener)
{

}

void GameScene::Update()
{
  bool use_ear = this->player_->IsUseEar();
  this->enemy_manager_->Update(this->player_);
  this->field_->Update(this->player_);
  this->boss_controller_->Update(this->player_);
  this->ui_player_->Update();

  if (!GameSceneDirector::GetInstance().Update())
  {
    if (!this->time_up_flag_)
    {
      if (!GameSceneDirector::GetInstance().IsGameOver())
      {
        this->text_time_up_->SetVisible(true);
      }
      this->timeup_text_show_time_ = TIME_UP_SHOW_TIME;
      this->time_up_flag_ = true;
    }
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

  T_UINT8 phase = GameSceneDirector::GetInstance().GetCurrentPhase();
  if (phase == GameConstants::PHASE_ZAKO && !this->zako_appear_flag_)
  {
    this->zako_appear_flag_ = true;
  }
  else if (phase == GameConstants::PHASE_BOSS && !this->boss_appear_flag_)
  {
    this->boss_appear_flag_ = true;
    this->zako_appear_flag_ = false;
    this->boss_controller_->Appear();
  }

  this->ui_player_->GetTimeView()->SetValue(GameSceneDirector::GetInstance().GetTimeCount() / 60);
  if (this->grand_slam_count_ > 0)
  {
    this->grand_slam_count_--;
//    this->bg_->GetTransform()->SetScale(1.0f - this->grand_slam_count_ * 0.002f);
  }
  if (this->weak_happy_count_ > 0)
  {
    this->weak_happy_count_--;
    this->boya_->GetMaterial()->GetDiffuse().SetAlpha(1.0f - ((T_FLOAT)this->weak_happy_count_ / WEAK_HAPPY));
  }
  if (this->damage_count_ > 0)
  {
    this->damage_count_--;
    const T_FLOAT damage_effect_rate = (T_FLOAT)this->damage_count_ / DAMAGE_EFFECT_TIME;
    this->boya_->GetMaterial()->GetDiffuse().SetRed(damage_effect_rate);
  }
  
  if (this->enemy_spawn_count_ < ENEMY_SPAWN_MAX && this->zako_appear_flag_ && rand() % ENEMY_SPWAN_PROBABILITY == 0)
  {
    this->enemy_spawn_count_++;
    this->enemy_manager_->SpawnToRandomPosition(this->player_);
  }
  
  if (this->enemy_manager_->AttackToPlayer(this->player_) || this->boss_controller_->AttackToPlayer(this->player_))
  {
    if (this->damage_count_ == 0)
    {
      this->damage_count_ = DAMAGE_EFFECT_TIME;
    }
  }

  if (this->player_->AttackToEnemy(this->enemy_manager_))
  {
    this->weak_happy_count_ = WEAK_HAPPY;
  }

  if (this->player_->AttackToBoss(this->boss_controller_))
  {
    this->weak_happy_count_ = WEAK_HAPPY;
  }

  if (this->enemy_manager_->AttackToPlayer(this->player_))
  {
    if (this->damage_count_ == 0)
    {
      this->damage_count_ = DAMAGE_EFFECT_TIME;
    }
  }
}

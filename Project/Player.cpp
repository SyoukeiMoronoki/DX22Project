#include "Player.h"
#include <algorithm>

#include "GameEntity.h"

#include "UI_Player.h"

#include "GameSceneDirector.h"

#include "GameConstants.h"
#include "GameInput.h"

#include "GameDirector.h"

#include "Asset.h"

static const T_UINT16 EAR_GAUGE_NEED = 100;
static const T_UINT16 EAR_GAUGE_DEC = 10;
static const T_UINT16 EAR_GAUGE_HEAL = 4;

static const T_UINT8 DEFAULT_POWER = 8;
static const T_UINT8 ATTACK_DELAY = 10;

Player::Player()
  : current_controller_(nullptr)
{
  this->actor_ = new PlayerActor(this);
  this->GetTransform()->SetY(0.5f);
  this->bullets_ = new BulletManager(10);
  this->walk_controller_ = new PlayerController_Walk(this);
  this->scope_controller_ = new PlayerController_Scope(this);
  this->collider_ = new Collider3D_Sphare(this);
  this->collider_->SetRadius(0.5f);
  this->bullet_effect_ = Sprite3D::CreateWithTexture(&Asset::Texture::PLAYER_BULLET_EFFECT);
  this->bullet_effect_->GetMaterial()->SetDiffuse(1.0f, 1.0f, 1.0f, 0.0f);
  this->bullet_effect_->GetMaterial()->SetZTestLevel(1);
  this->bullet_effect_->SetBillboardingFlag(true);
  //this->AddChild(this->bullet_effect_);
}

Player::~Player()
{
  delete this->actor_;
  delete this->bullets_;
  delete this->walk_controller_;
  delete this->scope_controller_;
}

void Player::GameInit()
{
  this->SetController(this->walk_controller_);

  this->AddChild(this->actor_);

  this->bullets_->AttachToEntity(GameDirector::GetScene()->GetRoot3d());

  this->control_delay_ = 0;
  this->attack_delay_ = 0;
  this->hp_ = GameConstants::HP_MAX;
  this->ear_gauge_ = GameConstants::EYE_GAUGE_MAX;
  this->use_ear_ = false;
  this->power_ = DEFAULT_POWER;

  this->OnEarChanged();
  this->OnHPChanged();
}

void Player::ControllProcess()
{
  using namespace HalEngine;
  using namespace GameInput;

  this->on_shot_ = false;
  this->bullet_effect_->GetMaterial()->SetDiffuse(Color4F::Lerp(this->bullet_effect_->GetMaterial()->GetDiffuse(), Color4F(1.0f, 1.0f, 1.0f, 0.0f), 0.25f));

  if (this->control_delay_ > 0)
  {
    return;
  }

  if (Input(0)->GetButtonDown(SCOPE))
  {
    if (this->current_controller_ == this->scope_controller_)
    {
      this->SetController(this->walk_controller_);
    }
    else
    {
      this->SetController(this->scope_controller_);
    }
  }
  this->current_controller_->ControllProcess();

  if (attack_delay_ == 0)
  {
    if (Input(0)->GetButton(FIRE))
    {
      this->attack_delay_ = ATTACK_DELAY;
      this->current_controller_->OnAttack();
      this->bullets_->Emmision(this, this->current_controller_->GetBulletDirection());
      this->on_shot_ = true;
      this->bullet_effect_->GetMaterial()->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
      this->bullet_effect_->GetTransform()->SetPosition(this->current_controller_->GetBulletDirection());
    }
  }
  else
  {
    this->attack_delay_--;
  }    
  
  if (Input(0)->GetButtonDown(EYE))
  {
    if (!this->use_ear_ && this->ear_gauge_ >= EAR_GAUGE_NEED)
    {
      this->ear_gauge_ = (T_UINT16)std::max((T_INT32)0, (T_INT32)(this->ear_gauge_ - EAR_GAUGE_NEED));
      this->use_ear_ = true;
    }
    else
    {
      this->use_ear_ = false;
    }
  }
  if (this->ear_gauge_ == 0 || this->on_shot_)
  {
    this->use_ear_ = false;
  }
}

void Player::Update()
{
  this->bullets_->Update();
  this->ControllProcess();

  if (this->use_ear_)
  {
    this->ear_gauge_ = (T_UINT16)std::max((T_INT32)0, (T_INT32)(this->ear_gauge_ - EAR_GAUGE_DEC));
    if (this->ear_gauge_ == 0)
    {
      this->use_ear_ = false;
    }
  }
  else
  {
    this->ear_gauge_ = (T_UINT16)std::min((T_UINT16)GameConstants::EYE_GAUGE_MAX, (T_UINT16)(this->ear_gauge_ + EAR_GAUGE_HEAL));
  }
  this->OnEarChanged();
}

void Player::AddControlDelay(T_UINT16 delay)
{
  this->control_delay_ += delay;
}

void Player::SetControlDelay(T_UINT16 delay)
{
  this->control_delay_ = delay;
}

void Player::SetControlDelayNegative(T_UINT16 delay)
{
  this->control_delay_ = std::max(this->control_delay_, delay);
}

void Player::SetView(UI_Player* view)
{
  this->view_ = view;

  this->OnHPChanged();
  this->OnEarChanged();
}

bool Player::AddDamage()
{
  if (this->hp_ == 0)
  {
    return false;
  }
  this->hp_--;
  this->OnHPChanged();
  return true;
}

void Player::OnHPChanged()
{
  this->view_->GetHPView()->SetValue(this->hp_);
}

void Player::OnEarChanged()
{
  this->view_->GetEarView()->SetValue(this->ear_gauge_);
}

void Player::AttackToEnemy(EnemyManager* enemys)
{
  std::vector<Bullet*> hited_bullet_ = std::vector<Bullet*>();
  std::map<Bullet*, std::deque<Enemy*>> results = std::map<Bullet*, std::deque<Enemy*>>();
  this->bullets_->Loop([&](Bullet* bullet)
  {
    bool hited= enemys->HitCheck(bullet);
    hited_bullet_.push_back(bullet);
  });

  this->bullets_->GetHitEntities(enemys, &results);
  for (auto itr = results.begin(); itr != results.end(); ++itr)
  {
    Bullet* bullet = itr->first;
    for (Enemy* enemy : itr->second)
    {
      enemy->OnWeakPointDamaged();
      bullet->OnHitEnemy();
    }
  }

}

void Player::SetController(PlayerController* controller)
{
  if (this->current_controller_)
  {
    this->current_controller_->End();
  }
  PlayerController* const prev = this->current_controller_;
  this->current_controller_ = controller;
  this->current_controller_->Start(prev);
}

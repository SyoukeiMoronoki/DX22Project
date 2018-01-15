#include "Player.h"
#include <algorithm>

#include "GameEntity.h"

#include "UI_Player.h"

#include "GameSceneDirector.h"

#include "GameConstants.h"
#include "GameInput.h"

#include "GameDirector.h"

static const T_UINT8 DEFAULT_POWER = 8;
static const T_UINT8 ATTACK_DELAY = 10;

Player::Player()
  : current_controller_(nullptr)
{
  this->actor_ = new PlayerActor(this);
  this->bullets_ = new BulletManager(10);
  this->walk_controller_ = new PlayerController_Walk(this);
  this->scope_controller_ = new PlayerController_Scope(this);
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
  this->ear_gauge_ = 0;
  this->use_ear_ = false;
  this->power_ = DEFAULT_POWER;

  this->OnEarChanged();
  this->OnHPChanged();
}

bool Player::ControllProcess()
{
  using namespace HalEngine;
  using namespace GameInput;
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
  if (this->control_delay_ > 0)
  {
    return false;
  }
  this->current_controller_->ControllProcess();
  bool fire = false;

  if (attack_delay_ == 0)
  {
    if (Input(0)->GetButton(FIRE))
    {
      fire = true;
      this->attack_delay_ = ATTACK_DELAY;
      this->current_controller_->OnAttack();
      this->bullets_->Emmision(this, this->current_controller_->GetBulletDirection());
    }
  }
  else
  {
    this->attack_delay_--;
  }    
  
  if (Input(0)->GetButtonDown(EYE))
  {
    this->use_ear_ = !this->use_ear_;
  }
  if (this->ear_gauge_ < 50)
  {
    this->use_ear_ = false;
  }

  return fire;
}

void Player::Update()
{
  this->ControllProcess();
  this->bullets_->Update();

  if (this->use_ear_)
  {
    this->ear_gauge_ = (T_UINT16)std::max((T_INT32)0, (T_INT32)(this->ear_gauge_ - 1));
    if (this->ear_gauge_ == 0)
    {
      this->use_ear_ = false;
    }
  }
  else
  {
    this->ear_gauge_ = (T_UINT16)std::min((T_UINT16)GameConstants::EYE_GAUGE_MAX, (T_UINT16)(this->ear_gauge_ + 2));
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
  std::map<Bullet*, std::deque<Enemy*>> results = std::map<Bullet*, std::deque<Enemy*>>();
  this->bullets_->GetHitEntities(enemys, &results);
  for (auto itr = results.begin(); itr != results.end(); ++itr)
  {
    Bullet* bullet = itr->first;
    for (Enemy* enemy : itr->second)
    {
      enemy->OnWeakPointDamaged();
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

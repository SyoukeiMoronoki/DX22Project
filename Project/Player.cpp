#include "Player.h"
#include <algorithm>

#include "GameEntity.h"

#include "UI_Player.h"

#include "GameSceneDirector.h"

#include "GameConstants.h"
#include "GameInput.h"

#include "GameDirector.h"

#include "Asset.h"

#include "BossController.h"

static const T_UINT16 EAR_GAUGE_NEED = 100;
static const T_UINT16 EAR_GAUGE_DEC = 4;
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
}

Player::~Player()
{
  delete this->collider_;
  delete this->scope_controller_;
  delete this->walk_controller_;
  delete this->bullets_;
  delete this->actor_;
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
  if (this->ear_gauge_ == 0)
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

bool Player::AttackToEnemy(EnemyManager* enemys)
{
  std::vector<Bullet*> hited_bullet_ = std::vector<Bullet*>();
  std::map<Bullet*, std::deque<Enemy*>> results = std::map<Bullet*, std::deque<Enemy*>>();
  bool weak_point_hit = false;
  this->bullets_->Loop([&](Bullet* bullet)
  {
    EnemyManager::HitResult hited = enemys->HitCheck(bullet);
    if (hited == EnemyManager::NO_HIT)
    {
      return;
    }
    if (hited == EnemyManager::HIT_WEAK_POINT)
    {
      weak_point_hit = true;
    }
    hited_bullet_.push_back(bullet);
  });
  for (Bullet* bullet : hited_bullet_)
  {
    this->bullets_->Free(bullet);
  }
  return weak_point_hit;
}

bool Player::AttackToBoss(BossController* boss)
{
  if (!boss->IsEnabld())
  {
    return false;
  }
  std::vector<Bullet*> hited_bullet_ = std::vector<Bullet*>();
  std::map<Bullet*, std::deque<BossBody*>> results = std::map<Bullet*, std::deque<BossBody*>>();
  bool weak_point_hit = false;
  this->bullets_->Loop([&](Bullet* bullet)
  {
    BossController::HitResult hited = boss->HitCheck(bullet);
    if (hited == BossController::NO_HIT)
    {
      return;
    }
    if (hited == BossController::HIT_WEAK_POINT)
    {
      weak_point_hit = true;
    }
    hited_bullet_.push_back(bullet);
  });
  for (Bullet* bullet : hited_bullet_)
  {
    this->bullets_->Free(bullet);
  }
  return weak_point_hit;
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

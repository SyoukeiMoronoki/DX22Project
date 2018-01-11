#include "Player.h"
#include <algorithm>

#include "GameEntity.h"

#include "UI_Player.h"
#include "UI_Cursol.h"

#include "GameSceneDirector.h"

#include "GameConstants.h"
#include "GameInput.h"

#include "GameDirector.h"

static const T_UINT8 DEFAULT_POWER = 8;
static const T_UINT8 ATTACK_DELAY = 10;

Player::Player()
{
  this->bullets_ = new BulletManager(10);
}

Player::~Player()
{}

void Player::GameInit()
{
  this->mae_ = new Cube3D();
  this->mae_->SetLightingEnabled(false);
  this->mae_->GetTransform()->SetY(-0.5f);
  this->mae_->GetTransform()->SetZ(0.5f);
  this->mae_->GetTransform()->SetScale(0.01f, 0.01f, 1.5f);
  this->AddChild(this->mae_);
  this->camera_ = new Camera3D_LookAt();
  Scene* scene = GameDirector::GetScene();
  this->camera_->GetRenderState()->AddTargetLayerId(0);
  scene->AddCamera(this->camera_);
  this->camera_->SetPlayer(this);

  this->bullets_->AttachToEntity(scene->GetRoot3d());

  this->cursol_pos_ = TVec2f(0.0f, 0.0f);
  this->control_delay_ = 0;
  this->attack_delay_ = 0;
  this->hp_ = GameConstants::HP_MAX;
  this->ear_gauge_ = 0;
  this->use_ear_ = false;
  this->power_ = DEFAULT_POWER;

  this->OnCursolChanged();
  this->OnEarChanged();
  this->OnHPChanged();
}

bool Player::ControllProcess()
{
  if (this->control_delay_ > 0)
  {
    return false;
  }
  bool fire = false;
  const T_FLOAT w = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
  const T_FLOAT h = (T_FLOAT)Director::GetInstance()->GetScreenHeight();
  //this->cursol_pos_.x = HalEngine::Input(0)->GetAxis(GameInput::SCREEN_X, 0.0f) * w;
  //this->cursol_pos_.y = HalEngine::Input(0)->GetAxis(GameInput::SCREEN_Y, 0.0f) * h;

  const T_FLOAT drx = HalEngine::Input(0)->GetAxis(GameInput::SCREEN_X, 0.0f);
  const T_FLOAT dry = HalEngine::Input(0)->GetAxis(GameInput::SCREEN_Y, 0.0f);
  const T_FLOAT LOOK_AT_X_MAX = 10.0f;
  const T_FLOAT LOOK_AT_Y_MAX = 10.0f;
  const T_FLOAT look_at_pos_x = std::min(LOOK_AT_X_MAX, std::max(-LOOK_AT_X_MAX, this->camera_->GetLookAtPosX() + drx));
  const T_FLOAT look_at_pos_y = std::min(LOOK_AT_Y_MAX, std::max(-LOOK_AT_Y_MAX, this->camera_->GetLookAtPosY() - dry));
  this->camera_->SetLookAtPosX(look_at_pos_x);
  this->camera_->SetLookAtPosY(look_at_pos_y);
  //this->camera_->GetTransform()->GetRotator()->RotateXAxis(0.1f);
  //if (dry != 0.0f)
  //{
  //}
  //if (drx != 0.0f)
  //{
  //  this->camera_->GetTransform()->GetRotator()->RotateYAxis(drx);
  //}

  const T_FLOAT dx = HalEngine::Input(0)->GetAxis(GameInput::X_AXIS);
  const T_FLOAT dy = HalEngine::Input(0)->GetAxis(GameInput::Y_AXIS);
  this->GetTransform()->GetRotator()->RotateY(dx * 0.1f);
  this->GetTransform()->MoveZ(dy * 0.5f);

  this->OnCursolChanged();

  if (this->cursol_pos_.x < -w * 0.4f)
  {
    this->view_angle_ -= 0.02f;
  }
  else if (this->cursol_pos_.x > w * 0.4f)
  {
    this->view_angle_ += 0.02f;
  }
  else if (this->cursol_pos_.x < -w * 0.3f)
  {
    this->view_angle_ -= 0.005f;
  }
  else if (this->cursol_pos_.x > w * 0.3f)
  {
    this->view_angle_ += 0.005f;
  }

  if (this->view_angle_ > 1.0f)
  {
    this->view_angle_ -= 1.0f;
  }
  else if (this->view_angle_ < 0.0f)
  {
    this->view_angle_ += 1.0f;
  }

  //this->viewport_.SetCameraAngleRad(this->view_angle_ * MathConstants::PI2);

  if (this->view_angle_ < 0.1f)
  {
    this->view_angle_ = this->view_angle_ * 1.0f;
  }

  using namespace EngineInput::Digital;
  if (attack_delay_ == 0)
  {
    if (HalEngine::Input(0)->GetButton(GameInput::FIRE))
    {
      fire = true;
      this->attack_delay_ = ATTACK_DELAY;
      this->cursol_view_->OnAttack();
      this->bullets_->Emmision(this, this->camera_->GetDirection());
    }
  }
  else
  {
    this->attack_delay_--;
  }
  if (this->use_ear_)
  {
    if (!HalEngine::Input(0)->GetButton(GameInput::EYE))
    {
      this->use_ear_ = false;
    }
  }
  else if (this->ear_gauge_ > 50 && HalEngine::Input(0)->GetButton(GameInput::EYE))
  {
    this->use_ear_ = true;
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

bool Player::PayCost(T_UINT8 cost)
{
  return true;
}

void Player::SetView(UI_Player* view, UI_Cursol* cursol)
{
  this->view_ = view;
  this->cursol_view_ = cursol;

  this->OnHPChanged();
  this->OnEarChanged();
  this->OnCursolChanged();
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

void Player::OnCursolChanged()
{
  this->cursol_view_->UpdatePosition(this->cursol_pos_);
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

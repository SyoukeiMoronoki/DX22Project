#include "Player.h"
#include <algorithm>

#include "GameEntity.h"

#include "CardManager.h"

#include "CardFactory.h"
#include "Vehicle.h"

Player::Player(const PlayerEntry& entry)
  : id_(entry.id)
  , status_(new PlayerStatus(entry.animal_data, entry.handicap))
  , controller_(entry.controller)
  , speed_(0.0f)
{
  this->body_ = new Cube3D();
  this->body_->SetLightingEnabled(false);
  this->AddChild(this->body_);
  this->AddChild(entry.camera);
  entry.camera->RegisterToPlayer(this);
  this->AddCollider(0.5f);
}

Player::~Player()
{
  delete this->body_;
  delete this->status_;
}

void Player::CardProcess(const PlayerInput& input, CardFacade* facade)
{
  PlayerInput::CommandKind command = input.GetCommandInput();
  if (command == PlayerInput::PLAYER_COMMAND_NONE)
  {
    return;
  }
  //Card* card = this->vehicle_current_->GetCardManager()->GetCard(command);
  //if (!card)
  //{
  //  return;
  //}
}

void Player::PreUpdate()
{
  PlayerInput input = PlayerInput();
  this->controller_->InputProcess(&input);

  const T_FLOAT rot_speed = this->status_->GetRotationSpeed();
  const T_FLOAT vx = input.GetVectorInput().x * rot_speed;
  const T_FLOAT vy = input.GetVectorInput().y * rot_speed;
  const T_FLOAT vz = input.GetVectorInput().z * rot_speed;
  this->GetTransform()->GetRotator()->RotateY(vx);
  this->GetTransform()->GetRotator()->RotateX(-vy);
  this->GetTransform()->GetRotator()->RotateZ(vz);
}

void Player::Update()
{
  this->speed_ = std::min(this->status_->GetMaxSpeed(), this->speed_ + this->status_->GetAccel());
  this->GetTransform()->MoveZ(this->speed_);
}

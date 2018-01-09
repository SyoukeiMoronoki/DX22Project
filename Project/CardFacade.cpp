#include "CardFacade.h"

#include "Player.h"
#include "AttackManager.h"
#include "AttackDataTable.h"

void CardFacade::Player_Boost(T_FLOAT speed, T_UINT8 delay)
{
  EntityModifierRoot* modifier = EntityModifierFactory::Root(
    EntityModifierFactory::Round(
      EntityModifierFactory::ScaleFromTo(5, 1.0f, 2.0f)
    )
  );
  //this->player_->AddForce(this->player_->GetTransform()->GetDirection() * speed);
}

void CardFacade::Player_ThrowTrap(T_FLOAT throw_length, T_FLOAT trap_radius)
{
  const TVec3f player_pos = this->player_->GetTransform()->GetPosition();
  const TVec3f landing_point = player_pos + this->player_->GetTransform()->GetDirection() * throw_length;
}

void CardFacade::Player_ThrowBomb(T_FLOAT throw_length, T_FLOAT bomb_radius)
{
  //const TVec3f player_pos = this->player_->GetTransform()->GetPosition();
  //const TVec3f landing_point = player_pos + this->player_->GetTransform()->GetDirection() * throw_length;
  //AttackFacade_Attach facade;
  //facade.SetPlayer(this->player_);
  //this->attack_manager_->Spawn(AttackDataTable::GetAttackData(AttackDataTable::ATTACK_KIND_BOMB), &facade);
}

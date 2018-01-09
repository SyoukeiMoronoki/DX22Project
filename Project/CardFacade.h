#pragma once

#include <HalEngine.h>

class Player;
class AttackManager;

class CardFacade
{
public:
  void Player_Boost(T_FLOAT speed, T_UINT8 delay);
  void Player_ThrowTrap(T_FLOAT throw_length, T_FLOAT trap_radius);
  void Player_ThrowBomb(T_FLOAT throw_length, T_FLOAT bomb_radius);

public:
  inline void SetPlayer(Player* player)
  {
    this->player_ = player;
  }

  inline void SetAttackManager(AttackManager* attack_manager)
  {
    this->attack_manager_ = attack_manager;
  }

private:
  Player* player_;
  AttackManager* attack_manager_;
};
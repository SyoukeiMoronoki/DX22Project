#pragma once

#include "Player.h"
#include "PlayerManager.h"
#include "AttackManager.h"

class CollisionHelper
{
public:
  //�v���C���[�ƒ��f�I�u�W�F�N�g�Ƃ̓����蔻��
  void Player_Object(Player* player);

  //�v���C���[�ƓG/�����I�u�W�F�N�g�̓����蔻��
  void Player_Attack(std::list<Player*>* players);

public:
  inline void SetAttackManager(AttackManager* manager)
  {
    this->attack_manager_ = manager;
  }
private:

  AttackManager* attack_manager_;
};

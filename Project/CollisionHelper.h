#pragma once

#include "Player.h"
#include "PlayerManager.h"
#include "AttackManager.h"

class CollisionHelper
{
public:
  //プレイヤーと中庸オブジェクトとの当たり判定
  void Player_Object(Player* player);

  //プレイヤーと敵/味方オブジェクトの当たり判定
  void Player_Attack(std::list<Player*>* players);

public:
  inline void SetAttackManager(AttackManager* manager)
  {
    this->attack_manager_ = manager;
  }
private:

  AttackManager* attack_manager_;
};

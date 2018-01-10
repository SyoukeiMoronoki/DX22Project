#pragma once

#include "Player.h"

class CollisionHelper
{
public:
  //プレイヤーと中庸オブジェクトとの当たり判定
  void Player_Object(Player* player);

  //プレイヤーと敵/味方オブジェクトの当たり判定
  void Player_Attack(std::list<Player*>* players);

private:

};

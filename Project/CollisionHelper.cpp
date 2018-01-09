#include "CollisionHelper.h"

void CollisionHelper::Player_Object(Player* player)
{
  //プレイヤーとボックスの当たり判定
  //ItemBox* hit_box_to_player = this->item_box_manager_->GetHitEntity_GameEntity(player);
  //if (hit_box_to_player)
  //{
  //  hit_box_to_player->OnHitToPlayer(player);
  //  //this->camera_->AddTargetEntity(hit_box_to_player);
  //  player->OnHitOther(hit_box_to_player);
  //}

  //プレイヤーの周りを周回するエナジーとボックスの当たり判定
  //std::map<ItemBox*, std::deque<Energy*>> hit_box_to_energy_map;
  //this->item_box_manager_->GetHitEntities_GameEntities(player->GetEnergyManager(), &hit_box_to_energy_map);
  //for (std::map<ItemBox*, std::deque<Energy*>>::iterator itr1 = hit_box_to_energy_map.begin(); itr1 != hit_box_to_energy_map.end(); ++itr1)
  //{
  //  ItemBox* const box = itr1->first;
  //  std::deque<Energy*>* hun_list = &(itr1->second);
  //  for (std::deque<Energy*>::iterator itr2 = hun_list->begin(); itr2 != hun_list->end(); ++itr2)
  //  {
  //    Energy* const hun = (*itr2);
  //    hun->OnItemCatched(box);
  //    box->OnHitToHun(hun);
  //  }
  //}

  //プレイヤーとアイテムの当たり判定
  //std::deque<Item*> hit_item_to_player_list;
  //this->item_manager_->GetHitEntities_GameEntity(player, &hit_item_to_player_list);
  //for (std::deque<Item*>::iterator itr = hit_item_to_player_list.begin(); itr != hit_item_to_player_list.end(); ++itr)
  //{
  //  Item* const item = (*itr);
  //  item->OnHitToPlayer(player);
  //}

  //プレイヤーの周りを周回するエナジーとアイテムの当たり判定
  //std::map<Item*, std::deque<Energy*>> hit_item_to_energy_map;
  //this->item_manager_->GetHitEntities_GameEntities(player->GetEnergyManager(), &hit_item_to_energy_map);
  //for (std::map<Item*, std::deque<Energy*>>::iterator itr1 = hit_item_to_energy_map.begin(); itr1 != hit_item_to_energy_map.end(); ++itr1)
  //{
  //  Item* const item = itr1->first;
  //  std::deque<Energy*>* hun_list = &(itr1->second);
  //  for (std::deque<Energy*>::iterator itr2 = hun_list->begin(); itr2 != hun_list->end(); ++itr2)
  //  {
  //    Energy* const hun = (*itr2);
  //    hun->OnItemCatched(item);
  //    item->Gravitate(player);
  //  }
  //}
}

void CollisionHelper::Player_Attack(std::list<Player*>* players)
{
  std::deque<Attack*> hit_attacks;
  for (std::list<Player*>::iterator itr = players->begin(); itr != players->end(); ++itr)
  {
    Player* const player = (*itr);
    //敵攻撃との判定
    this->attack_manager_->GetHitAttacks(player, &hit_attacks);
    for (std::deque<Attack*>::iterator itr = hit_attacks.begin(); itr != hit_attacks.end(); ++itr)
    {
      Attack* atk = (*itr);
      //player->OnHitAttack(atk);
    }
  }

  //プレイヤーの攻撃とアイテムボックスの当たり判定
  //std::map<ItemBox*, std::deque<Attack*>> hit_attacks_to_itembox;
  //this->attack_manager_->GetHitAttacks(this->item_box_manager_, &hit_attacks_to_itembox);
  //for (std::map<ItemBox*, std::deque<Attack*>>::iterator itr1 = hit_attacks_to_itembox.begin(); itr1 != hit_attacks_to_itembox.end(); ++itr1)
  //{
  //  ItemBox* const box = itr1->first;
  //  std::deque<Attack*>* const list = &itr1->second;
  //  for (std::deque<Attack*>::iterator itr2 = list->begin(); itr2 != list->end(); ++itr2)
  //  {
  //    Attack* atk = (*itr2);
  //    box->OnDamaged(atk->GetAttackData()->power);
  //  }
  //}
}

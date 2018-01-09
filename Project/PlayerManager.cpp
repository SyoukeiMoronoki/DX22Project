#include "PlayerManager.h"

#include "CollisionHelper.h"
#include "CardFacade.h"

#include "GameDirector.h"

PlayerManager::PlayerManager(const std::vector<PlayerEntry*>& entries)
  : players_()
{
  for (PlayerEntry* entry : entries)
  {
    this->players_.push_back(new Player(*entry));
  }
}

PlayerManager::~PlayerManager()
{
  for (Player* player : this->players_)
  {
    player->RemoveSelf();
    delete player;
  }
}

void PlayerManager::Loop(std::function<void(Player*)> func)
{
  for (Player* player : this->players_)
  {
    func(player);
  }
}

void PlayerManager::LoopIncludingPool(std::function<void(Player*)> func)
{
  for (Player* player : this->players_)
  {
    func(player);
  }
}

Player* PlayerManager::Select(std::function<bool(Player*)> condition)
{
  for (Player* player : this->players_)
  {
    if (condition(player))
    {
      return player;
    }
  }
  return nullptr;
}

void PlayerManager::SelectAll(std::deque<Player*>* dest, std::function<bool(Player*)> condition)
{
  for (Player* player : this->players_)
  {
    if (condition(player))
    {
      dest->push_back(player);
    }
  }
}

void PlayerManager::AttachAdditionToField()
{
  //this->sun_attack_manager_->AttachToField(field, z_index_attack);
  //this->moon_attack_manager_->AttachToField(field, z_index_attack);
}

void PlayerManager::DetachAdditionFromField()
{
  //this->sun_attack_manager_->DetachFromField();
  //this->moon_attack_manager_->DetachFromField();
}

void PlayerManager::Collision(CollisionHelper* helper)
{
  std::list<Player*> players;
  this->Loop([&](Player* p)
  {
    players.push_front(p);
  });
  T_UINT8 size = 0;
  while (0 < (size = (T_UINT8)players.size()))
  {
    const T_UINT8 key = Util::GetRandom(size);
    std::list<Player*>::iterator itr = players.begin();
    for (T_UINT8 i = 0; i < key; ++i)
    {
      itr++;
    }
    helper->Player_Object(*itr);
    players.erase(itr);
  }

  //ƒvƒŒƒCƒ„[“¯m‚Ì“–‚½‚è”»’è
  //for (std::list<Player*>::iterator itr = this->players_.begin(); itr != this->players_.end(); ++itr)
  //{
  //  Player* const sun_player = (*itr);
  //  for (std::list<Player*>::iterator itr2 = this->players_.begin(); itr2 != this->players_.end(); ++itr2)
  //  {
  //    Player* const moon_player = (*itr2);
  //    if (!Collision::Circle_Circle(*sun_player->GetCollider(), *moon_player->GetCollider()))
  //    {
  //      continue;
  //    }
  //    sun_player->OnHitOtherPlayer(moon_player);
  //  }
  //}


  ////sun‘¤‚Ì“–‚½‚è”»’èˆ—
  //helper->SetAttackManager(this->moon_attack_manager_);
  //helper->Player_Attack(&this->sun_players_);

  ////moon‘¤‚Ì“–‚½‚è”»’èˆ—
  //helper->SetAttackManager(this->sun_attack_manager_);
  //helper->Player_Attack(&this->moon_players_);

}
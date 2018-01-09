#include "AttackManager.h"

AttackManager::AttackManager(T_UINT16 attack_count_)
{
  this->attack_count_ = attack_count_;
  this->attacks_ = new Attack*[this->attack_count_];
  for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  {
    this->attacks_[i] = new Attack();
    this->attacks_[i]->SetVisible(false);
  }
}

AttackManager::~AttackManager()
{
  if (!this->attacks_)
  {
    return;
  }
  for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  {
    if (!this->attacks_[i])
    {
      continue;
    }
    delete this->attacks_[i];
  }
  delete[] this->attacks_;
}

void AttackManager::Update()
{
  //AttackFacade facade;
  //for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  //{
  //  if (!this->attacks_[i]->IsVisible())
  //  {
  //    continue;
  //  }
  //  facade.SetAttack(this->attacks_[i]);
  //  this->attacks_[i]->Update(&facade);
  //}
}

void AttackManager::Spawn(const AttackData* data, AttackFacade_Attach* facade)
{
  //Attack* attack = GetReadyAttack();
  //if (!attack)
  //{
  //  return;
  //}
  //facade->SetAttack(attack);
  //attack->Spawn(data, facade);
  //attack->SetVisible(true);
}

Attack* AttackManager::GetHitAttack(GameEntity* entity)
{
  //for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  //{
  //  if (!this->attacks_[i]->IsVisible())
  //  {
  //    continue;
  //  }
  //  if (this->attacks_[i]->CollisionCheckToGameEntity(entity))
  //  {
  //    return this->attacks_[i];
  //  }
  //}
  return nullptr;
}

void AttackManager::GetHitAttacks(GameEntity* entity, std::deque<Attack*>* dest)
{
  //dest->clear();
  //for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  //{
  //  if (!this->attacks_[i]->IsVisible())
  //  {
  //    continue;
  //  }
  //  if (this->attacks_[i]->CollisionCheckToGameEntity(entity))
  //  {
  //    dest->push_back(this->attacks_[i]);
  //  }
  //}
}

void AttackManager::AttachToField(GameObject3D* entity)
{
  for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  {
    entity->AddChild(this->attacks_[i]);
  }
}

void AttackManager::DetachFromField()
{
  for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  {
    this->attacks_[i]->RemoveSelf();
  }
}

Attack* AttackManager::GetReadyAttack() const
{
  for (T_UINT16 i = 0; i < this->attack_count_; ++i)
  {
    if (this->attacks_[i]->IsVisible())
    {
      continue;
    }
    return this->attacks_[i];
  }
  return nullptr;
}

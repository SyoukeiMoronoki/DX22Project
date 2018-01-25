#include "BossController.h"
#include "BossBrain.h"
#include "BossBrainTable.h"
#include "BossBulletManager.h"

static const T_UINT8 BOSS_BODY_COUNT = 30;
static const T_FLOAT SPEED = 0.3f;

BossController::BossController()
  : AllocatableGameEntityManager(BOSS_BODY_COUNT)
{
  for (T_UINT8 i = 0; i < BOSS_BODY_COUNT; ++i)
  {
    BossBody* body = this->Allocate();
    body->SetVisible(false);
    body->GetTransform()->SetY(10.0f);
  }
  this->bullets_ = new BossBulletManager(200);
  this->speed_ = SPEED;
  this->brain_ = nullptr;
  this->enabled_ = false;
}

void BossController::Appear()
{
  this->enabled_ = true;
  this->Loop([](BossBody* body)
  {
    body->SetVisible(true);
  });
}

void BossController::Update(Player* player)
{
  if (!this->enabled_)
  {
    return;
  }
  this->bullets_->Update();
  BossBody* head = this->Select([](BossBody*) { return true; });
  if (!this->brain_)
  {
    this->ChangeBrain(BossBrainTable::GetBossBrain(BossBrainTable::BRAIN_AROUND), head, player);
  }
  head->HeadUpdate(this, player);

  BossBody* front = head;
  this->Loop([&](BossBody* body)
  {
    if (body == head)
    {
      return;
    }
    body->BodyUpdate(this, front, player);
    front = body;
  });
}

void BossController::ChangeBrain(BossBrain* brain, BossBody* head, Player* player)
{
  this->brain_ = brain;
  this->brain_->Init(this, head, player);
}

bool BossController::AttackToPlayer(Player* player)
{
  return false;
}

BossController::HitResult BossController::HitCheck(Bullet* bullet)
{
  BossBody* body= this->Select([&](BossBody* enemy)
  {
    return enemy->HitCheck(bullet->GetCollider());
  });
  if (body)
  {
    if (body->IsWeak())
    {
      body->OnWeakPointDamaged();
      return HIT_WEAK_POINT;
    }
    body->OnDamaged();
    return HIT_BODY;
  }
  return HitResult::NO_HIT;
}

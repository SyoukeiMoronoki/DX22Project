#pragma once

#include <HalEngine.h>

#include "BulletManager.h"
#include "EnemyManager.h"
#include "PlayerController_Walk.h"
#include "PlayerController_Scope.h"
#include "PlayerActor.h"

class GameEntity;
class UI_Player;
class PlayerUI_Player;
class BossController;

class Player : public GameObject3D
{
public:
  Player();
  ~Player();

public:
  void GameInit();

  void ControllProcess();
  void Update() override;

public:
  void AddControlDelay(T_UINT16 delay);
  void SetControlDelay(T_UINT16 delay);
  //�Œ���K�v�ȃf�B���C����́B���ɂ���ȏ�̃f�B���C������Ή������Ȃ�
  void SetControlDelayNegative(T_UINT16 delay);

  void SetView(UI_Player* view);

  bool AddDamage();

  void OnHPChanged();
  void OnEarChanged();

  bool AttackToEnemy(EnemyManager* enemys);
  bool AttackToBoss(BossController* boss);

protected:
  void SetController(PlayerController* controller);

public:
  inline T_UINT8 GetPower() const
  {
    return this->power_;
  }
  inline bool IsUseEar() const
  {
    return this->use_ear_;
  }
  inline bool OnShot() const
  {
    return this->on_shot_;
  }
  inline T_UINT16 GetHP() const
  {
    return this->hp_;
  }
  inline PlayerActor* GetActor() const
  {
    return this->actor_;
  }
  inline Collider3D_Sphare* GetCollider() const
  {
    return this->collider_;
  }
  inline const PlayerController* GetController() const
  {
    return this->current_controller_;
  }
  inline Quaternion GetWorldQuaternion() const
  {
    return this->GetTransform()->GetQuaternion() * this->actor_->GetDirectionQuaternion();
  }

private:
  PlayerController_Scope* scope_controller_;
  PlayerController_Walk* walk_controller_;
  PlayerController* current_controller_;
  Collider3D_Sphare * collider_;

  PlayerActor* actor_;
  
  T_UINT16 control_delay_;
  T_UINT8 attack_delay_;

  T_UINT16 hp_;

  T_UINT16 ear_gauge_;
  bool use_ear_;

  bool on_shot_;
  
  T_UINT8 power_;

  UI_Player* view_;

  BulletManager* bullets_;
};


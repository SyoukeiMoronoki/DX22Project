#pragma once

#include <HalEngine.h>

#include "BulletManager.h"
#include "EnemyManager.h"

class GameEntity;
class UI_Player;
class UI_Cursol;

class Player : public GameObject3D
{
public:
  Player();
  ~Player();

public:
  void GameInit();

  bool ControllProcess();
  void Update() override;

public:
  void AddControlDelay(T_UINT16 delay);
  void SetControlDelay(T_UINT16 delay);
  //最低限必要なディレイを入力。既にそれ以上のディレイがあれば何もしない
  void SetControlDelayNegative(T_UINT16 delay);

  bool PayCost(T_UINT8 cost);

  void SetView(UI_Player* view, UI_Cursol* cursol);

  bool AddDamage();

  void OnHPChanged();
  void OnEarChanged();
  void OnCursolChanged();

  void AttackToEnemy(EnemyManager* enemys);

public:
  inline T_UINT8 GetPower() const
  {
    return this->power_;
  }
  inline bool IsUseEar() const
  {
    return this->use_ear_;
  }
  inline T_UINT16 GetHP() const
  {
    return this->hp_;
  }

private:
  Cube3D* mae_;

  Camera3D_LookAt* camera_;
  TVec2f cursol_pos_;

  T_UINT16 control_delay_;
  T_UINT8 attack_delay_;

  T_UINT16 hp_;

  T_UINT16 ear_gauge_;
  bool use_ear_;
  
  T_UINT8 power_;
  T_FLOAT view_angle_;

  UI_Cursol* cursol_view_;
  UI_Player* view_;

  BulletManager* bullets_;

};


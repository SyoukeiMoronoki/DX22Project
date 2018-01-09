#include "AttackAttribute_Bomb.h"

#include "../Engine/EntityModifierFactory.h"


AttackAttribute_Bomb::AttackAttribute_Bomb(T_FLOAT radius, T_FLOAT throw_power)
  : radius_(radius)
  , throw_power_(throw_power)
{}

void AttackAttribute_Bomb::OnAttach(AttackFacade_Attach* facade) const
{
  //AttackCollider_Circle* collider = new AttackCollider_Circle();
  //collider->SetRadius(this->radius_);
  //facade->AttachColliderToAttack(collider);
  //const TVec3f& user_pos = facade->GetUserPosition();
  //const TVec3f& user_direction = facade->GetUserDirection();

  //EntityModifier* m1_1 = EntityModifierFactory::TranslateFromTo(20, user_pos, user_pos + user_direction.Normalized() * this->throw_power_);
  //EntityModifier* m1_2 = EntityModifierFactory::ColorFromTo(20, Color::BLACK, Color::RED);
  //EntityModifier* m1 = EntityModifierFactory::Synchronized(m1_1, m1_2);
  //m1->SetEasingFunction(EasingFunction::FK_EXPONENTIAL, EasingFunction::EASE_IN);

  //EntityModifier* m2_1 = EntityModifierFactory::ScaleFromTo(20, 1.0f, 5.0f);
  //EntityModifier* m2_2_1 = EntityModifierFactory::ColorFromTo(10, Color::WHITE, Color::YELLOW);
  //EntityModifier* m2_2_2 = EntityModifierFactory::ColorTo(10, Color::RED);
  //EntityModifier* m2_2 = EntityModifierFactory::Sequence(m2_2_1, m2_2_2);
  //EntityModifier* m2 = EntityModifierFactory::Synchronized(m2_1, m2_2);

  //EntityModifier* m3_1 = EntityModifierFactory::ScaleTo(20, 10);
  //EntityModifier* m3_2 = EntityModifierFactory::ColorTo(20, Color(0, 0, 0, 0));
  //EntityModifier* m3 = EntityModifierFactory::Synchronized(m3_1, m3_2);

  //EntityModifier* m = EntityModifierFactory::Sequence(m1, m2, m3);

  //EntityModifierRoot* root = EntityModifierFactory::Root(m);
  //facade->AttachModifierToAttack(root);
}

void AttackAttribute_Bomb::OnDetach(AttackFacade* facade) const
{
//  facade->DeleteAttackCollider();
}

bool AttackAttribute_Bomb::OnUpdate(AttackFacade* facade) const
{
  return true;
}

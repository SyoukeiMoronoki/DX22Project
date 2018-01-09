#include "Attack.h"
#include "../Engine/Director.h"

#include "IAttackAttribute.h"

Attack::Attack()
  : data_(nullptr)
{
}

Attack::~Attack()
{
}

void Attack::Update(AttackFacade* facade)
{
  if (this->data_->attribute->OnUpdate(facade))
  {
    return;
  }
  this->data_->attribute->OnDetach(facade);
  this->SetVisible(false);
}

void Attack::Spawn(const AttackData* data, AttackFacade_Attach* facade)
{
  this->data_ = data;
  this->data_->attribute->OnAttach(facade);
  this->GetTransform()->SetScale(1.0f);
  this->GetTransform()->GetRotator()->SetEularAngles(0.0f, 0.0f, 0.0f);
}


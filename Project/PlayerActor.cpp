#include "PlayerActor.h"
#include "Asset.h"
#include "GameSceneDirector.h"

PlayerActor::PlayerActor(Player* player)
  : player_(player)
{
  //this->GetTransform()->SetEularY(MathConstants::PI_1_2);
  this->body_ = new Cube3D();
  this->body_->SetMaterial(Asset::Material::PLAYER_BODY);
  this->body_->UniqueMaterial();
  this->body_->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);
  this->body_->GetTransform()->SetPosition(0.0f, 0.01f, 0.0f);
  this->body_->SetLayerId(1);
  this->AddChild(this->body_);

  this->gun_ = new Cube3D();
  this->gun_->SetMaterial(Asset::Material::PLAYER_BODY);
  this->gun_->UniqueMaterial();
  this->gun_->GetMaterial()->SetDiffuse(Color4F::BLACK);
  this->gun_->GetTransform()->SetScale(0.1f, 0.1f, 1.0f);
  this->gun_->GetTransform()->SetPosition(0.0f, 0.0f, 0.5f);
  this->gun_->SetLayerId(1);
  this->AddChild(this->gun_);

  this->shadow_ = Sprite3D::CreateWithTexture(&Asset::Texture::PLAYER_SHADOW000);
  this->shadow_->SetMaterial(Asset::Material::PLAYER_SHADOW);
  this->shadow_->GetMaterial()->SetMainTexture(&Asset::Texture::PLAYER_SHADOW000);
  this->shadow_->GetTransform()->RotateX(MathConstants::DegToRad(90));
  this->shadow_->GetTransform()->SetY(-0.5f);
  this->AddChild(this->shadow_);
}

PlayerActor::~PlayerActor()
{
  delete this->body_;
  delete this->gun_;
  delete this->shadow_;
}

void PlayerActor::Update()
{
  this->GetTransform()->LerpRotation(this->direction_quaternion_, 0.25f);

  const Field* field = GameSceneDirector::GetInstance().GetField();
  
  this->body_->GetMaterial()->BoolProperty("_UseEar") = this->player_->IsUseEar();
  this->body_->GetMaterial()->ColorProperty("_Ambient") = field->GetFieldAmbientColor();

  this->gun_->GetMaterial()->BoolProperty("_UseEar") = this->player_->IsUseEar();
  this->gun_->GetMaterial()->ColorProperty("_Ambient") = field->GetFieldAmbientColor();
}

void PlayerActor::Walk(T_FLOAT x, T_FLOAT y)
{
  T_FLOAT rad = -atan2f(y, x) + MathConstants::PI_1_2;
  this->direction_quaternion_ = Quaternion(TVec3f(0.0f, 1.0f, 0.0f), rad);
}

void PlayerActor::Face(const Quaternion& direction_quaternion)
{
  this->direction_quaternion_ = direction_quaternion;
}

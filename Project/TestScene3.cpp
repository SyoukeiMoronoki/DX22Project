#include "TestScene3.h"

void TestScene3::OnLoad(IResourceLoadReserver* resource)
{
}

void TestScene3::OnSetup()
{
  this->camera_ = new Camera3D_LookAt();
  this->AddCamera(this->camera_);
  this->cube_ = Cube3D::Create();
  this->cube_->GetTransform()->SetZ(10.0f);
  this->AddChild(this->cube_);
}

void TestScene3::OnUnload()
{
  delete this->cube_;
}

void TestScene3::OnShow(ISceneShowListener* listener)
{
}

void TestScene3::OnHide(ISceneHideListener* listener)
{
}

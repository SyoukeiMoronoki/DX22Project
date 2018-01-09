#include "Star.h"
#include "Asset.h"

Star::Star()
{
  BillBoard* billboard = new BillBoard();
  billboard->SetTexture(Asset::Texture::STAR);
  billboard->SetBlendFunction(BlendFunction::BLEND_ADD_SRC, BlendFunction::BLEND_ADD_DST);
  billboard->SetZTestFlag(true);
  billboard->SetLightingEnabled(false);
  this->AddCollider(0.5f);
  this->body_ = billboard;
  this->AddChild(this->body_);
}

Star::~Star()
{
  delete this->body_;
}

void Star::OnAllocated()
{
  this->SetVisible(true);
}

void Star::OnFree()
{
}

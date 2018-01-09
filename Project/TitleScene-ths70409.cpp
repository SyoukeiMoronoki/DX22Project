#include "TitleScene.h"

#include "../Engine/Director.h"
#include "../Engine/EntityModifierFactory.h"
#include "../Engine/Util.h"

#include "TextureResource.h"
#include "ParticleResource.h"
#include "SpineResource.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "GameDirector.h"

static const T_UINT16 PARTICLE_COUNT = 0;
static const T_UINT16 SKELETON_COUNT = 0;

static const T_UINT16 GRID_COUNT = 100;
static const T_FLOAT GRID_PADDING = 100.0f / GRID_COUNT;
static const T_FLOAT GRID_LENGTH = GRID_PADDING * GRID_COUNT;

void TitleScene::OnLoad(SceneResource* resource)
{
  //Resource
  using namespace TextureResource;
  resource->LoadTexturePalette(PID_TITLE);
  resource->LoadParticleData();
  resource->LoadSpineData();

  //3D
  this->Create3DLayer(LAYER_BG);
  this->Create3DLayer(LAYER_MAIN);

  this->look_at_camera_ = new Camera3D_LookAt();
  this->look_at_camera_->AddTargetLayerId(LAYER_BG);
  this->look_at_camera_->AddTargetLayerId(LAYER_MAIN);
  //this->look_at_camera_->SetViewportWidth(Director::GetInstance()->GetScreenWidth() * 0.5f);
  this->AddCamera(this->look_at_camera_);

  this->look_at_camera_2_ = new Camera3D_LookAt();
  this->look_at_camera_2_->AddTargetLayerId(LAYER_BG);
  this->look_at_camera_2_->AddTargetLayerId(LAYER_MAIN);
  this->look_at_camera_2_->SetViewportWidth(Director::GetInstance()->GetScreenWidth() * 0.5f);
  this->look_at_camera_2_->SetViewportX(Director::GetInstance()->GetScreenWidth() * 0.5f);
  //this->AddCamera(this->look_at_camera_2_);

  this->cube_ = new Cube3D();
  //this->cube_->GetTransform()->SetScale(100.0f);
  this->line_ = new Line3D();
  this->line_->GetTransform()->SetX(3.0f);
  this->line_->GetTransform()->SetScale(100.0f);
  this->plane_ = new Plane3D();
  //this->plane_->GetTransform()->SetX(-3.0f);
  this->triangle_ = new Triangle3D();
  this->triangle_->GetTransform()->SetX(-3.0f);

  //2D
  this->Create2DLayer(LAYER_BG);

  this->camera_ = new Camera2D();
  this->camera_->AddTargetLayerId(LAYER_BG);
  this->AddCamera(this->camera_);

  this->floor_ = Sprite::CreateFromAsset(PID_TITLE, TID_TITLE_IMAGE);
  this->floor_->SetAlpha(192);
  this->floor_->SetZIndex(-1);

  T_FLOAT width = Director::GetInstance()->GetScreenWidth();
  T_FLOAT height = Director::GetInstance()->GetScreenHeight();

  for (T_UINT16 i = 0; i < PARTICLE_COUNT; ++i)
  {
    ParticleSystem* particle = ParticleSystem::CreateFromAsset(ParticleResource::PARTICLE_ID_BEAM);
    particle->SetApplyLocalPosition(false);
    particle->GetTransform()->SetX(-width * 0.5f + Util::GetRandom(0, width));
    particle->GetTransform()->SetY(-height * 0.5f + Util::GetRandom(0, height));
    particle->SetZIndex(2);
    this->particles_.push_back(particle);
  }

  for (T_UINT16 i = 0; i < SKELETON_COUNT; ++i)
  {
    SkeletonAnimation* skeleton = SkeletonAnimation::CreateFromAsset(SpineResource::SPINE_ID_ANUBIS);
    skeleton->GetTransform()->SetScale(0.05f);
    skeleton->GetTransform()->SetX(-width * 0.5f + Util::GetRandom(0, width));
    skeleton->GetTransform()->SetY(-height * 0.5f + Util::GetRandom(0, height));
    skeleton->setAnimation(0, "wait", true);
    this->skeletons_.push_back(skeleton);
  }

  this->grid_x_ = new Line3D*[GRID_COUNT];
  for (T_UINT16 i = 0; i < GRID_COUNT; ++i)
  {
    this->grid_x_[i] = new Line3D();
    this->grid_x_[i]->GetTransform()->SetScale(GRID_LENGTH);
    this->grid_x_[i]->GetTransform()->SetZ((i - (GRID_COUNT - 1) * 0.5f) * GRID_PADDING);
    this->grid_x_[i]->GetTransform()->SetRotationZ(MathConstants::DegToRad(90));
  }

  this->grid_y_ = new Line3D*[GRID_COUNT];
  for (T_UINT16 i = 0; i < GRID_COUNT; ++i)
  {
    this->grid_y_[i] = new Line3D();
    this->grid_y_[i]->GetTransform()->SetScale(GRID_LENGTH);
    this->grid_y_[i]->GetTransform()->SetX((i - (GRID_COUNT - 1) * 0.5f) * GRID_PADDING);
    this->grid_y_[i]->GetTransform()->SetRotationX(MathConstants::DegToRad(90));
  }

}

void TitleScene::OnUnload(SceneResource* resource)
{
  using namespace TextureResource;
  resource->UnloadParticleData();
  resource->UnloadTexturePalette(PID_TITLE);  
  resource->UnloadSpineData();
  if (this->floor_)
  {
    delete this->floor_;
    this->floor_ = nullptr;
  }
}

void TitleScene::OnShow()
{
  this->AddUpdateEventListener(this);
  this->AddEngineInputEventListener(this);
  //this->AddChild(this->sprite_);
  //this->AddChild(this->skeleton_);
  //this->Get3DLayer(LAYER_BG)->AddChild(this->cube_);
  //this->Get3DLayer(LAYER_BG)->AddChild(this->triangle_);
  //this->Get3DLayer(LAYER_BG)->AddChild(this->line_);
  //this->Get3DLayer(LAYER_BG)->AddChild(this->plane_);

  for (std::vector<ParticleSystem*>::iterator itr = this->particles_.begin(); itr != this->particles_.end(); ++itr)
  {
    this->Get2DLayer(LAYER_BG)->AddChild(*itr);
  }
  for (std::vector<SkeletonAnimation*>::iterator itr = this->skeletons_.begin(); itr != this->skeletons_.end(); ++itr)
  {
    this->Get2DLayer(LAYER_BG)->AddChild(*itr);
  }
  for (T_UINT16 i = 0; i < GRID_COUNT; ++i)
  {
    this->Get3DLayer(LAYER_MAIN)->AddChild(this->grid_x_[i]);
    this->Get3DLayer(LAYER_MAIN)->AddChild(this->grid_y_[i]);
  }
  //this->AddChild(this->particle2_);
}

void TitleScene::OnHide()
{
  this->RemoveUpdateEventListener(this);
  this->RemoveEngineInputEventListener(this);
  this->Get2DLayer(LAYER_BG)->RemoveChild(this->floor_);
}

bool TitleScene::OnUpdate(const UpdateEventState& state)
{
  static int cnt = 0;
  //this->line_->GetTransform()->SetRotationX(this->line_->GetTransform()->GetRotationX() + 0.1f);
  //this->line_->GetTransform()->SetRotationY(this->line_->GetTransform()->GetRotationY() + 0.2f);
  //this->line_->GetTransform()->SetRotationZ(this->line_->GetTransform()->GetRotationZ() + 0.3f);

  //this->cube_->GetTransform()->SetRotationX(this->cube_->GetTransform()->GetRotationX() + 0.1f);
  //this->cube_->GetTransform()->SetRotationY(this->cube_->GetTransform()->GetRotationY() + 0.2f);
  //this->cube_->GetTransform()->SetRotationZ(this->cube_->GetTransform()->GetRotationZ() + 0.3f);
  //T_FLOAT d = cnt / 60.0f;
  //this->cube_->GetTransform()->SetScaleX((T_FLOAT)sin(d) * 4.0f);
  //this->cube_->GetTransform()->SetScaleY((T_FLOAT)sin(d * 1.5) * 8.0f);
  //this->cube_->GetTransform()->SetScaleZ((T_FLOAT)sin(d * 2) * 12.0f);

  //this->triangle_->GetTransform()->SetRotationX(this->triangle_->GetTransform()->GetRotationX() + 0.1f);
  //this->triangle_->GetTransform()->SetRotationY(this->triangle_->GetTransform()->GetRotationY() + 0.2f);
  //this->triangle_->GetTransform()->SetRotationZ(this->triangle_->GetTransform()->GetRotationZ() + 0.1f);
  T_FLOAT d = cnt / 60.0f;
  for (T_UINT16 i = 0; i < GRID_COUNT; ++i)
  {
    T_FLOAT dv = sin(d + i * 0.02f);
    this->grid_x_[i]->GetTransform()->SetY(dv);
    this->grid_y_[i]->GetTransform()->SetY(dv);
  }
  cnt++;
  return true;
}

void TitleScene::OnEngineInput(const EngineInputState& state)
{
  using namespace EngineInput;
  const T_FLOAT spd = 16.0f;

  //if (
  //  state.GetDigitalInput(0)->IsTrigger(Digital::ID_LEFT) ||
  //  state.GetDigitalInput(0)->IsTrigger(Digital::ID_RIGHT) ||
  //  state.GetDigitalInput(0)->IsTrigger(Digital::ID_UP) ||
  //  state.GetDigitalInput(0)->IsTrigger(Digital::ID_DOWN)
  //  )
  //{
  //  Director::GetInstance()->ChangeScene(new GameScene());
  //  return;
  //}
  if (state.GetDigitalInput(0)->IsTrigger(Digital::ID_A))
  {
    GameDirector::GetInstance().GetPlayerEntryManager()->AddEntry(PlayerEntry::PLAYER_ENTRY_PLAYER);
  }
  if (state.GetDigitalInput(0)->IsTrigger(Digital::ID_B))
  {
    GameDirector::GetInstance().GetPlayerEntryManager()->AddEntry(PlayerEntry::PLAYER_ENTRY_COMPUTER);
  }

  if (
    state.GetDigitalInput(0)->IsTrigger(Digital::ID_Z)
    )
  {
    Director::GetInstance()->ChangeScene(new GameScene());
    return;
  }

  if (state.GetDigitalInput(0)->IsHold(Digital::ID_UP)) {
    this->look_at_camera_->SetCameraZ(this->look_at_camera_->GetCameraZ() + 0.2f);
    this->look_at_camera_->SetLookAtPosZ(this->look_at_camera_->GetLookAtPosZ() + 0.2f);
    this->look_at_camera_2_->SetCameraZ(this->look_at_camera_2_->GetCameraZ() + 0.2f);
    this->look_at_camera_2_->SetLookAtPosZ(this->look_at_camera_2_->GetLookAtPosZ() + 0.2f);
  }
  if (state.GetDigitalInput(0)->IsHold(Digital::ID_DOWN)) {
    this->look_at_camera_->SetCameraZ(this->look_at_camera_->GetCameraZ() - 0.2f);
    this->look_at_camera_->SetLookAtPosZ(this->look_at_camera_->GetLookAtPosZ() - 0.2f);
    this->look_at_camera_2_->SetCameraZ(this->look_at_camera_2_->GetCameraZ() - 0.2f);
    this->look_at_camera_2_->SetLookAtPosZ(this->look_at_camera_2_->GetLookAtPosZ() - 0.2f);
  }
  if (state.GetDigitalInput(0)->IsHold(Digital::ID_LEFT)) {
    this->look_at_camera_->SetCameraX(this->look_at_camera_->GetCameraX() - 0.2f);
    this->look_at_camera_->SetLookAtPosX(this->look_at_camera_->GetLookAtPosX() - 0.2f);
    this->look_at_camera_2_->SetCameraX(this->look_at_camera_2_->GetCameraX() + 0.2f);
    this->look_at_camera_2_->SetLookAtPosX(this->look_at_camera_2_->GetLookAtPosX() + 0.2f);
  }
  if (state.GetDigitalInput(0)->IsHold(Digital::ID_RIGHT)) {
    this->look_at_camera_->SetCameraX(this->look_at_camera_->GetCameraX() + 0.2f);
    this->look_at_camera_->SetLookAtPosX(this->look_at_camera_->GetLookAtPosX() + 0.2f);
    this->look_at_camera_2_->SetCameraX(this->look_at_camera_2_->GetCameraX() - 0.2f);
    this->look_at_camera_2_->SetLookAtPosX(this->look_at_camera_2_->GetLookAtPosX() - 0.2f);
  }

}

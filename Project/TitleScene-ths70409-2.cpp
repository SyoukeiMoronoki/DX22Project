#include "TitleScene.h"

#include "../Engine/Director.h"
#include "../Engine/EntityModifierFactory.h"
#include "../Engine/Util.h"
#include "../Engine/EasingFunctionManager.h"

#include "TextureResource.h"
#include "ParticleResource.h"
#include "SpineResource.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "GameDirector.h"

static const T_FLOAT SPEED = 0.1f;

static const T_UINT16 PARTICLE_COUNT = 0;
static const T_UINT16 SKELETON_COUNT = 0;

static const T_FLOAT GRID_LENGTH = 10.0f;
static const T_UINT16 GRID_COUNT = 10;
static const T_UINT16 GRID_LINE_COUNT = GRID_COUNT + 1;
static const T_FLOAT GRID_PADDING = GRID_LENGTH / GRID_COUNT;

/*
  頂点に法線情報を追加する
  FVFに法線を追加
  頂点情報に法線を正しく入れる
*/

void TitleScene::OnLoad(SceneResource* resource)
{
  //Resource
  using namespace TextureResource;
  resource->LoadTexturePalette(PID_TITLE);
  resource->LoadTexturePalette(PID_COMMON);
  resource->LoadParticleData();
  resource->LoadSpineData();

  //3D
  this->Create3DLayer(LAYER_BG);
  this->Create3DLayer(LAYER_MAIN);

  this->camera_ = new Camera3D_LookAt();
  this->camera_->AddTargetLayerId(LAYER_BG);
  this->camera_->AddTargetLayerId(LAYER_MAIN);
  this->camera_->SetViewportWidth(Director::GetInstance()->GetScreenWidth() * 0.5f);
  this->camera_->GetTransform()->SetRotationX(0.25f * MathConstants::PI);
  this->camera_->GetTransform()->SetZ(-10.0f);
  this->camera_->GetTransform()->SetY(10.0f);
  this->AddCamera(this->camera_);

  this->camera2_ = new Camera3D_LookAt();
  this->camera2_->AddTargetLayerId(LAYER_BG);
  this->camera2_->AddTargetLayerId(LAYER_MAIN);
  this->camera2_->SetViewportWidth(Director::GetInstance()->GetScreenWidth() * 0.5f);
  this->camera2_->SetViewportX(Director::GetInstance()->GetScreenWidth() * 0.5f);
  //this->camera2_->GetTransform()->SetZ(-1.5f);
  this->camera2_->GetTransform()->SetY(1.5f);
  this->AddCamera(this->camera2_);

  this->player_ = new Cube3D();
  this->player_->GetMaterial()->SetDiffuse(255, 0, 0, 255);
  this->player_->SetLightingEnabled(false);
  this->camera2_->SetPlayer(this->player_);

  this->cube_ = new Cube3D();
  this->line_ = new Line3D();
  this->line_->GetTransform()->SetX(3.0f);
  this->line_->GetTransform()->SetScale(100.0f);

  this->plane_ = new Plane3D();
  this->plane_->SetTexture(Director::GetInstance()->GetTexture(PID_COMMON, TID_COMMON_JUGYO_CUBE));
  this->plane_->GetTransform()->SetX(-3.0f);
  
  this->billboard_ = new BillBoard();
  this->billboard_->SetTexture(Director::GetInstance()->GetTexture(PID_COMMON, TID_COMMON_TEST_BUTTON));
  this->billboard_->GetTransform()->SetZ(10.0f);

  this->billboard2_ = new BillBoard();
  this->billboard2_->SetTexture(Director::GetInstance()->GetTexture(PID_COMMON, TID_COMMON_TEST_BUTTON));
  this->billboard2_->GetTransform()->SetZ(9.0f);
  
  this->triangle_ = new Triangle3D();
  this->triangle_->GetTransform()->SetX(-3.0f);

  this->grid_x_ = new Line3D*[GRID_LINE_COUNT];
  for (T_UINT16 i = 0; i < GRID_LINE_COUNT; ++i)
  {
    this->grid_x_[i] = new Line3D();
    this->grid_x_[i]->GetTransform()->SetScale(GRID_LENGTH);
    this->grid_x_[i]->GetTransform()->SetZ((i - GRID_COUNT * 0.5f) * GRID_PADDING);
    this->grid_x_[i]->GetTransform()->SetRotationZ(MathConstants::DegToRad(90));
  }
  this->grid_y_ = new Line3D*[GRID_LINE_COUNT];
  for (T_UINT16 i = 0; i < GRID_LINE_COUNT; ++i)
  {
    this->grid_y_[i] = new Line3D();
    this->grid_y_[i]->GetTransform()->SetScale(GRID_LENGTH);
    this->grid_y_[i]->GetTransform()->SetX((i - GRID_COUNT * 0.5f) * GRID_PADDING);
    this->grid_y_[i]->GetTransform()->SetRotationX(MathConstants::DegToRad(90));
  }

  const T_FLOAT length = GRID_PADDING * GRID_COUNT * 0.5f - GRID_PADDING * 0.5f;

  TVec3f cube_coords[CUBE_COUNT] =
  {
    { -length, 0.5f, length },
    { length, 0.5f, length },
    { -length, 0.5f, -length },
    { length, 0.5f, -length },
  };

  for (T_UINT16 i = 0; i < CUBE_COUNT; ++i)
  {
    this->cubes_[i] = new Cube3D();
    this->cubes_[i]->SetTexture(Director::GetInstance()->GetTexture(PID_COMMON, TID_COMMON_JUGYO_CUBE));
    this->cubes_[i]->GetTransform()->SetPositon(cube_coords[i]);
  }

  this->light_ = new Light();
  this->light_->Apply();
  NativeMethod::Graphics().Graphics_Cheat(1);

  this->angle_ = 0.0f;

  this->model_ = new Model("Asset/model/cart/cart.x");
  this->model_->GetTransform()->SetRotationY(MathConstants::DegToRad(180));
  this->model_->GetTransform()->SetZ(2.0f);

  this->model2_ = new Model("Asset/model/cart/cart.x");
  this->model2_->GetTransform()->SetScale(3.0f);

  this->targetable_.push_back(this->cubes_[0]);
  this->targetable_.push_back(this->cubes_[1]);
  this->targetable_.push_back(this->cubes_[2]);
  this->targetable_.push_back(this->cubes_[3]);
  this->targetable_.push_back(this->billboard_);

  this->target_id_ = this->targetable_.size();

  //2D
  this->Create2DLayer(LAYER_BG);

  this->camera2d_ = new Camera2D();
  this->camera2d_->AddTargetLayerId(LAYER_BG);
  this->AddCamera(this->camera2d_);

  this->floor_ = Sprite::CreateFromAsset(PID_TITLE, TID_TITLE_IMAGE);
  this->floor_->SetAlpha(192);
  this->floor_->SetZIndex(-1);

  T_FLOAT width = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
  T_FLOAT height = (T_FLOAT)Director::GetInstance()->GetScreenHeight();

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

}

void TitleScene::OnUnload(SceneResource* resource)
{
  using namespace TextureResource;
  resource->UnloadParticleData();
  resource->UnloadTexturePalette(PID_TITLE);
  resource->UnloadTexturePalette(PID_COMMON);
  resource->UnloadSpineData();
  if (this->floor_)
  {
    delete this->floor_;
    this->floor_ = nullptr;
  }
}

void TitleScene::OnShow()
{
  NativeMethod::Graphics().Graphics_SetLightingEnabled(false);
  this->AddUpdateEventListener(this);
  this->AddEngineInputEventListener(this);
  //this->AddChild(this->sprite_);
  //this->AddChild(this->skeleton_);
  //this->Get3DLayer(LAYER_BG)->AddChild(this->camera2_->GetEntity());
  //this->camera2_->GetEntity()->AddChild(this->cube_);
  //this->Get3DLayer(LAYER_BG)->AddChild(this->triangle_);
  //this->Get3DLayer(LAYER_BG)->AddChild(this->line_);
  this->Get3DLayer(LAYER_BG)->AddChild(this->player_);
  this->Get3DLayer(LAYER_BG)->AddChild(this->plane_);
  this->Get3DLayer(LAYER_BG)->AddChild(this->model2_);
  this->Get3DLayer(LAYER_BG)->AddChild(this->billboard_);
  this->Get3DLayer(LAYER_BG)->AddChild(this->billboard2_);
  this->player_->AddChild(this->model_);


  for (std::vector<ParticleSystem*>::iterator itr = this->particles_.begin(); itr != this->particles_.end(); ++itr)
  {
    this->Get2DLayer(LAYER_BG)->AddChild(*itr);
  }
  for (std::vector<SkeletonAnimation*>::iterator itr = this->skeletons_.begin(); itr != this->skeletons_.end(); ++itr)
  {
    this->Get2DLayer(LAYER_BG)->AddChild(*itr);
  }
  for (T_UINT16 i = 0; i < CUBE_COUNT; ++i)
  {
    this->Get3DLayer(LAYER_MAIN)->AddChild(this->cubes_[i]);
  }
  for (T_UINT16 i = 0; i < GRID_LINE_COUNT; ++i)
  {
    this->Get3DLayer(LAYER_MAIN)->AddChild(this->grid_x_[i]);
    this->Get3DLayer(LAYER_MAIN)->AddChild(this->grid_y_[i]);
  }
  //this->AddChild(this->particle2_);
  //using namespace TextureResource;
  //Sprite* sprite = Sprite::CreateFromAsset(PID_COMMON, TID_COMMON_JUGYO_CUBE);
  //this->Get2DLayer(LAYER_BG)->AddChild(sprite);
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
  using namespace EasingFunction;
  T_FLOAT d = cnt / 60.0f;
  for (T_UINT16 i = 0; i < GRID_LINE_COUNT; ++i)
  {
    //T_FLOAT dv = sin(d + i * 0.02f);
    //T_FLOAT dv = sin(sin(sin(sin(d + i * 0.02f) * MathConstants::PI) * MathConstants::PI * 2) * MathConstants::PI);
    //this->grid_x_[i]->GetTransform()->SetY(dv);
    //this->grid_y_[i]->GetTransform()->SetY(dv);
  }

  T_FLOAT v = sin(d);
  this->cubes_[CUBE_LEFT_UP]->GetTransform()->SetX(this->cubes_[CUBE_LEFT_UP]->GetTransform()->GetX() + (double)rand() / RAND_MAX - 0.5f);
  this->cubes_[CUBE_LEFT_UP]->GetTransform()->SetY(this->cubes_[CUBE_LEFT_UP]->GetTransform()->GetY() + (double)rand() / RAND_MAX - 0.5f);
  this->cubes_[CUBE_LEFT_UP]->GetTransform()->SetZ(this->cubes_[CUBE_LEFT_UP]->GetTransform()->GetZ() + (double)rand() / RAND_MAX - 0.5f);
  this->cubes_[CUBE_RIGHT_UP]->GetTransform()->SetScale(v + 1.5f);
  this->cubes_[CUBE_LEFT_DOWN]->GetTransform()->SetRotationX(v * MathConstants::PI * 2.0f);
  this->cubes_[CUBE_LEFT_DOWN]->GetTransform()->SetRotationY(v * MathConstants::PI * 2.0f);
  this->cubes_[CUBE_LEFT_DOWN]->GetTransform()->SetRotationZ(v * MathConstants::PI * 2.0f);

  this->cubes_[CUBE_RIGHT_DOWN]->GetTransform()->MoveZ(0.1f);
  this->cubes_[CUBE_RIGHT_DOWN]->GetTransform()->RotationYAxis(0.1f);

  cnt++;

  this->camera2_->Update();
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
  // Director::GetInstance()->ChangeScene(new GameScene());
  //  return;
  //}
  if (state.GetDigitalInput(0)->IsHold(Digital::ID_UP)) {
    this->player_->GetTransform()->MoveZ(SPEED);
  }
  else if (state.GetDigitalInput(0)->IsHold(Digital::ID_DOWN)) {
    this->player_->GetTransform()->MoveZ(-SPEED);
  }

  this->light_->SetDirection(this->camera2_->GetDirection());
  this->light_->Apply();

  T_INT8 v = 0;
  if (state.GetDigitalInput(0)->IsTrigger(Digital::ID_L1)) {
    v = -1;
  }
  else if (state.GetDigitalInput(0)->IsTrigger(Digital::ID_R1)) {
    v = 1;
  }
  this->target_id_ = std::min((T_INT8)this->targetable_.size() + 1, std::max(0, (T_INT8)this->target_id_ + v));

  //ターゲット中
  if (this->target_id_ < this->targetable_.size())
  {
    GameObject3D* target = this->targetable_[this->target_id_];
    this->camera2_->SetTarget(target);

    if (state.GetDigitalInput(0)->IsHold(Digital::ID_LEFT)) {
      this->player_->GetTransform()->MoveX(-SPEED);
    }
    else if (state.GetDigitalInput(0)->IsHold(Digital::ID_RIGHT)) {
      this->player_->GetTransform()->MoveX(SPEED);
    }

    TVec3f direction = this->camera2_->GetDirection();
    T_FLOAT ang = atan2(direction.z, direction.x) - MathConstants::PI * 0.5f;
    this->player_->GetTransform()->SetRotationY(ang);
  }
  //ターゲット無し
  else
  {
    this->camera2_->SetTarget(nullptr);
    if (state.GetDigitalInput(0)->IsHold(Digital::ID_LEFT)) {
      this->player_->GetTransform()->RotationYAxis(-0.1f);
    }
    else if (state.GetDigitalInput(0)->IsHold(Digital::ID_RIGHT)) {
      this->player_->GetTransform()->RotationYAxis(0.1f);
    }

    //カメラ単体で見渡す処理
    T_FLOAT camera_rotate_dy = 0.0f;
    if (state.GetDigitalInput(0)->IsHold(Digital::ID_C)) {
      camera_rotate_dy = 0.1f;
    }
    else if (state.GetDigitalInput(0)->IsHold(Digital::ID_A)) {
      camera_rotate_dy = -0.1f;
    }
    if (camera_rotate_dy != 0.0f)
    {
      this->camera2_->SetLookAtPosX(this->camera2_->GetLookAtPosX() + camera_rotate_dy);
      this->camera_rotated_y_ += camera_rotate_dy;
    }
    else
    {
      T_FLOAT elastic_y = this->camera_rotated_y_;
      this->camera_rotated_y_ *= 0.9f;
      elastic_y -= this->camera_rotated_y_;
      this->camera2_->SetLookAtPosX(this->camera2_->GetLookAtPosX() - elastic_y);
    }

    T_FLOAT camera_rotate_dx = 0.0f;
    if (state.GetDigitalInput(0)->IsHold(Digital::ID_B))
    {
      camera_rotate_dx = -0.1f;
    }
    else if (state.GetDigitalInput(0)->IsHold(Digital::ID_Z))
    {
      camera_rotate_dx = 0.1f;
    }
    if (camera_rotate_dx != 0.0f)
    {
      this->camera2_->SetLookAtPosY(this->camera2_->GetLookAtPosY() + camera_rotate_dx);
      this->camera_rotated_x_ += camera_rotate_dx;
    }
    else
    {
      T_FLOAT elastic_x = this->camera_rotated_x_;
      this->camera_rotated_x_ *= 0.9f;
      elastic_x -= this->camera_rotated_x_;
      this->camera2_->SetLookAtPosY(this->camera2_->GetLookAtPosY() - elastic_x);
    }
  }

}

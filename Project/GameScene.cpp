#include "GameScene.h"
#include "GameDirector.h"
#include "Asset.h"

GameScene::GameScene()
  : player_manager_(nullptr)
{
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Model::SKYBOX);
  resource->ReserveLoad(Asset::Texture::STAR);
}

void GameScene::OnSetup()
{
  this->player_manager_ = new PlayerManager(GameDirector::GetPlayerEntries());
  this->star_manager_ = new StarManager(GameDirector::GetGameSetting().GetLevelParam().star_levels);
  this->skydome_ = new Model(Asset::Model::SKYBOX);
  this->skydome_->SetLightingEnabled(false);

  this->GetRoot3d()->AddChild(this->skydome_);
  this->player_manager_->AttachToEntity(this->GetRoot3d());
  this->star_manager_->AttachToEntity(this->GetRoot3d());
}

void GameScene::OnUnload()
{
  this->player_manager_->DetachFromEntity();
  this->star_manager_->DetachFromEntity();

  delete this->player_manager_;
  delete this->star_manager_;
}

void GameScene::OnShow(ISceneShowListener* listener)
{
}

void GameScene::OnHide(ISceneHideListener* listener)
{
}

void GameScene::Update()
{
  this->star_manager_->Update();

  std::map<Player*, std::deque<Star*>> hited_stars = std::map<Player*, std::deque<Star*>>();
  this->player_manager_->GetHitEntities(this->star_manager_, &hited_stars);

  for (auto pair : hited_stars)
  {
    Player* player = pair.first;
    for (Star* star : pair.second)
    {
      star->GetTransform()->SetScale(0.1f);
      //star->RemoveSelf();
      //player->AddChild(star);
    }
  }
}

#include "StarManager.h"

StarManager::StarManager(const LevelParam& level_param)
  : AllocatableGameEntityManager(level_param.star_count)
  , level_param_(level_param)
  , count_(0)
{
}

void StarManager::Update()
{
  this->count_++;
  while (this->count_ > this->level_param_.star_spawn_delay)
  {
    this->count_ -= this->level_param_.star_spawn_delay;
    Star* star = this->Allocate();
    if (!star)
    {
      continue;
    }
    const T_FLOAT rad_x = Util::GetRandom(-1.0f, 1.0f);
    const T_FLOAT rad_y = Util::GetRandom(-1.0f, 1.0f);
    const T_FLOAT rad_z = Util::GetRandom(-1.0f, 1.0f);
    const T_FLOAT distance = Util::GetRandom(this->level_param_.star_spawn_radius);
    const T_FLOAT scale = Util::GetRandom(this->level_param_.star_scale_min, this->level_param_.star_scale_max);
    star->GetTransform()->SetPosition(TVec3f(rad_x, rad_y, rad_z).Normalized() * distance);
    star->GetTransform()->SetScale(scale);
  }
}

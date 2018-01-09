#include "GameSetting.h"

GameSetting::GameSetting(IPlayerEntryListBuilder* entry_list_builder)
  : level_param_()
  , entry_list_builder_(entry_list_builder)
{}

GameSetting::~GameSetting()
{
  delete this->entry_list_builder_;
}

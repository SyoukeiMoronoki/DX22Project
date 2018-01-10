#pragma once

namespace ParticleResource
{

enum PaletteID
{
  PID_TITLE,
  PID_GAME,

  PID_DATANUM,
};

static const char* PalettePaths[PID_DATANUM] =
{
  "title",
  "game",
};

enum ParticleID_Title
{
  TID_TITLE_IMAGE,
};

enum ParticleID_Game
{
  TID_GAME_PLAYER,
  TID_GAME_ATTACK_BOMB,

  TID_GAME_DATANUM
};

}


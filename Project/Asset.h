#pragma once
#include <HalEngine.h>

namespace Asset
{

namespace Spine
{
extern SpineResource TEST;
extern SpineResource ANUBIS;
}; // namespace Spine

namespace Model
{
extern ModelData CART;
extern ModelData SKYBOX;
extern ModelData DOITYU;
}; // namespace Model

namespace FBX
{
//extern FbxResource NEKO;
}; // namespace FBX

namespace Texture
{ 
extern class Texture ENEMY_WEAK_POINT;
extern class Texture ENEMY_ZAKO1;
extern class Texture ENEMY_ZAKO2;
extern class Texture ENEMY_BOSS;

extern class Texture FIELD_GROUND;
extern class Texture FIELD_GROUND_NORMAL;
extern class Texture FIELD_BOYA;

extern class Texture FONT_NUMBER;

extern class Texture PLAYER_BULLET;
extern class Texture PLAYER_BULLET_EFFECT;
extern class Texture PLAYER_TURGET;

extern class Texture TEXT_BONUS;
extern class Texture TEXT_HP;
extern class Texture TEXT_PRESSBUTTON;
extern class Texture TEXT_RESULT;
extern class Texture TEXT_SCORE;
extern class Texture TEXT_SONAR;
extern class Texture TEXT_TIME;
extern class Texture TEXT_TIMEUP;
extern class Texture TEXT_TITLE;

extern class Texture UI_EARGAUGE;
extern class Texture UI_HPGAUGE;
extern class Texture UI_PLAYER_ID;
extern class Texture UI_TEATER;
extern class Texture UI_KEYBOARD;
};// namespace Texture

namespace Shader
{
extern const ShaderResource SKY;
extern const ShaderResource ZENITH;
extern const ShaderResource ENEMY_BODY;
extern const ShaderResource ENEMY_SHADOW;
extern const ShaderResource GROUND;
} // namespace Shader

namespace Material
{
extern class Material SKY;
extern class Material ZENITH;
extern class Material ENEMY_BODY;
extern class Material ENEMY_SHADOW;
extern class Material GROUND;
} // namespace Material

}; // namespace Asset
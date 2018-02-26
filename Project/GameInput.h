#pragma once

#include <HalEngine.h>

//GameInput
//ゲームの入力を定義する
namespace GameInput
{

//新しいボタン入力を定義したい時はこの列挙型に追加していく
//追加した場合、cppファイル側にボタンの詳細を定義していく
enum Kind
{
  X_AXIS, //X軸入力
  Y_AXIS, //Y軸入力
  SCREEN_X, //X軸画面上位置
  SCREEN_Y, //Y軸画面上位置
  FOCUS,  //視点を合わせる
  FIRE,   //ショット
  EYE,    //眼
  SCOPE,  //スコープ

  GAME_INPUT_DATANUM, //ここは触らない
};

//ここは触らない
const InputEntity* GetInputEntities();

}
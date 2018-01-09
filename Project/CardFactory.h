#pragma once

#include "CardData.h"
#include "Card.h"

namespace CardFactory
{
enum CardKind
{
  //スカラベ状態ではチャージして3コスト使用のSP版を使う事ができる
  //スカラベ状態では苦手カードを使用する際コストが２倍必要
  //カー状態だとチャージが必要なのは変わらないが、コスト１でSP版を使用できる
  //カー状態では更に長いチャージをする事でコスト7使用のEX版の使用も可能

  //使用した瞬間加速する
  //得意
  //アトゥム(Atum)
  // SP ⇒ 敵に当たった場合画面端まで吹き飛ばす事ができる
  // EX ⇒ 一定時間常時ブースト状態になる
  //トート(Thoth)
  // SP ⇒ 敵陣営の時間を0.5秒停止させて動く事ができる
  // EX ⇒ 敵陣営の時間を7秒停止させて動く事ができる
  //苦手
  //ケプリ ⇒ コスト２倍
  //アヌビス ⇒ コスト２倍
  CARD_KIND_BOOSTER,
  CARD_KIND_BOOSTER_SP_ATUM,
  CARD_KIND_BOOSTER_EX_ATUM,
  CARD_KIND_BOOSTER_SP_THOTH,
  CARD_KIND_BOOSTER_EX_THOTH,

  //着弾した後広がり罠となるフンを飛ばす
  //罠はカーの速度を遅めるほか、敵陣営がフンを生成できず、味方陣営はフンを生成しやすい
  //時間経過や、キャラが上を通る度に縮小し、一定以下の大きさになったら消滅する
  //得意
  //ケプリ(Khepri)  　
  // SP ⇒ 触れた罠を吸収し大きくなる特別な罠をしかける。後に生成された方が優先
  // EX ⇒ 画面内の罠を全て吸収し、一つの巨大な罠にする
  //アヌビス(Anubis)
  // SP ⇒ 罠の代わりにアヌビスホールを設置
  //    アヌビスホール ⇒ 踏んだ敵陣営キャラを自分の目の前に連れてきて停止させる
  //                     味方陣営キャラの場合はダッシュパネルとなる
  //                    一度効果を発動したら消滅
  // EX ⇒ タメが長く範囲が狭いがゲーム上唯一のプレイヤーを死亡させる技を放つ
  //    死亡 ⇒ 集めた半分のアイテムを吐き出し、初期状態に戻る。
  //苦手
  //ラー ⇒ コスト２倍
  //セシャト ⇒ コスト２倍
  CARD_KIND_TRAP,
  CARD_KIND_TRAP_SP_KHEPRI,
  CARD_KIND_TRAP_EX_KHEPRI,
  CARD_KIND_TRAP_SP_ANUBIS,
  CARD_KIND_TRAP_EX_ANUBIS,

  //飛ばして一定距離進むと爆発するフンを飛ばす
  //得意
  //ラー(Ra)
  // SP ⇒ ボムの代わりに一瞬で無間遠方まで届くレーザーになる。
  // EX ⇒ 数秒間レーザーを出し続ける。薙ぎ払う事もできる。連続ヒットする。
  //セシャト(Seschat)
  // SP ⇒ 敵を追尾するボムを放つ
  // EX ⇒ 敵を追尾するボムを7個放つ
  //苦手
  //アトゥム ⇒ コスト２倍
  //トート ⇒ コスト２倍
  CARD_KIND_BOMB,
  CARD_KIND_BOMB_SP_RA,
  CARD_KIND_BOMB_EX_RA,
  CARD_KIND_BOMB_SP_SESCHAT,
  CARD_KIND_BOMB_EX_SESCHAT,

  CARD_KIND_AMARI,

  CARD_KIND_DATANUM,
};

Card* CreateCard(CardKind kind);

};
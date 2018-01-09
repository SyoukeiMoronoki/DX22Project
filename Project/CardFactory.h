#pragma once

#include "CardData.h"
#include "Card.h"

namespace CardFactory
{
enum CardKind
{
  //�X�J���x��Ԃł̓`���[�W����3�R�X�g�g�p��SP�ł��g�������ł���
  //�X�J���x��Ԃł͋��J�[�h���g�p����ۃR�X�g���Q�{�K�v
  //�J�[��Ԃ��ƃ`���[�W���K�v�Ȃ͕̂ς��Ȃ����A�R�X�g�P��SP�ł��g�p�ł���
  //�J�[��Ԃł͍X�ɒ����`���[�W�����鎖�ŃR�X�g7�g�p��EX�ł̎g�p���\

  //�g�p�����u�ԉ�������
  //����
  //�A�g�D��(Atum)
  // SP �� �G�ɓ��������ꍇ��ʒ[�܂Ő�����΂������ł���
  // EX �� ��莞�ԏ펞�u�[�X�g��ԂɂȂ�
  //�g�[�g(Thoth)
  // SP �� �G�w�c�̎��Ԃ�0.5�b��~�����ē��������ł���
  // EX �� �G�w�c�̎��Ԃ�7�b��~�����ē��������ł���
  //���
  //�P�v�� �� �R�X�g�Q�{
  //�A�k�r�X �� �R�X�g�Q�{
  CARD_KIND_BOOSTER,
  CARD_KIND_BOOSTER_SP_ATUM,
  CARD_KIND_BOOSTER_EX_ATUM,
  CARD_KIND_BOOSTER_SP_THOTH,
  CARD_KIND_BOOSTER_EX_THOTH,

  //���e������L����㩂ƂȂ�t�����΂�
  //㩂̓J�[�̑��x��x�߂�ق��A�G�w�c���t���𐶐��ł����A�����w�c�̓t���𐶐����₷��
  //���Ԍo�߂�A�L���������ʂ�x�ɏk�����A���ȉ��̑傫���ɂȂ�������ł���
  //����
  //�P�v��(Khepri)  �@
  // SP �� �G�ꂽ㩂��z�����傫���Ȃ���ʂ�㩂���������B��ɐ������ꂽ�����D��
  // EX �� ��ʓ���㩂�S�ċz�����A��̋����㩂ɂ���
  //�A�k�r�X(Anubis)
  // SP �� 㩂̑���ɃA�k�r�X�z�[����ݒu
  //    �A�k�r�X�z�[�� �� ���񂾓G�w�c�L�����������̖ڂ̑O�ɘA��Ă��Ē�~������
  //                     �����w�c�L�����̏ꍇ�̓_�b�V���p�l���ƂȂ�
  //                    ��x���ʂ𔭓����������
  // EX �� �^���������͈͂��������Q�[����B��̃v���C���[�����S������Z�����
  //    ���S �� �W�߂������̃A�C�e����f���o���A������Ԃɖ߂�B
  //���
  //���[ �� �R�X�g�Q�{
  //�Z�V���g �� �R�X�g�Q�{
  CARD_KIND_TRAP,
  CARD_KIND_TRAP_SP_KHEPRI,
  CARD_KIND_TRAP_EX_KHEPRI,
  CARD_KIND_TRAP_SP_ANUBIS,
  CARD_KIND_TRAP_EX_ANUBIS,

  //��΂��Ĉ�苗���i�ނƔ�������t�����΂�
  //����
  //���[(Ra)
  // SP �� �{���̑���Ɉ�u�Ŗ��ԉ����܂œ͂����[�U�[�ɂȂ�B
  // EX �� ���b�ԃ��[�U�[���o��������B�ガ���������ł���B�A���q�b�g����B
  //�Z�V���g(Seschat)
  // SP �� �G��ǔ�����{�������
  // EX �� �G��ǔ�����{����7����
  //���
  //�A�g�D�� �� �R�X�g�Q�{
  //�g�[�g �� �R�X�g�Q�{
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
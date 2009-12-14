#ifndef LCD_H
#define LCD_H

/************************************************************
 * SC1602 LCD �R���g���[������p���C�u����
 ************************************************************/

#include "common.h"

#define LCD_BLANK "                "

/*
 * LCD �R���g���[��������������֐�
 */
void lcd_init(void);

/************************************************************
 * �����^�\���֐�
 *   LCD �R���g���[���Ƃ̒ʐM���I���܂Ŋ֐�����߂�Ȃ��\������֐��Q
 *************************************************************/

// �\���ʒu�� tx, ty �Ɉړ�����
void lcd_position( uint8_t tx, uint8_t ty);

// ���݂̕\���ʒu�� ch ��\������
void lcd_put_ch(uint8_t ch);

// ���݂̕\���ʒu���� ch �� 16 �i�\������
void lcd_put_hex2ch(uint8_t ch);

// ���݂̕\���ʒu���當�����\������(2��ڂɐ܂�Ԃ��Ȃ�)
void lcd_put_str( uint8_t *str );

// �\����S�N���A
void lcd_clear_all( void );

// ��i�̂ݕ\���N���A
void lcd_clear_upper( void );

// ���i�̂ݕ\���N���A
void lcd_clear_lower( void );


/************************************************************
 * �񓯊��^�\���֐�
 *   lcd_display ���s���܂ł� LCD �R���g���[���Ƃ̒ʐM���������Ȃ��\������֐��Q
 *************************************************************/
#define LCD_UPPER 0  // LCD ��i
#define LCD_LOWER 1  // LCD ���i
#define LCD_ROW 2    // LCD �̍s��
#define LCD_COL 16   // LCD �̗�

extern uint8_t lcd_dirty[LCD_ROW];

/*
 * �\�����ׂ��f�[�^���c���Ă���Ƃ��� true ��Ԃ�
 *  lcd_display �̓����ł����l�̃`�F�b�N�����Ă��邽�߁A
 *  lcd_display ���ĂԑO�ɖ{�}�N���𗘗p����K�v�͂Ȃ��B
 */
#define lcd_has_data_to_display() (lcd_dirty[LCD_UPPER] || lcd_dirty[LCD_LOWER])

/*
 * �\���f�[�^��ݒ肷��֐�
 *  data: �\�����镶����
 *  row: �\������s
 *  col: �\���J�n�̗�
 *  hex8: 16 �i�ŕ\������ 1�o�C�g�̒l
 *  hex16: 16 �i�ŕ\������ 2�o�C�g�̒l
 *  len: data �̒���
 */
void lcd_set_data( uint8_t *data, uint8_t row, uint8_t col, size_t len );
void lcd_set_hex8( uint8_t hex8, uint8_t row, uint8_t col );
void lcd_set_hex16( uint16_t hex16, uint8_t row, uint8_t col );

/*
 * �\���o�b�t�@���N���A����
 *  row: �\������s
 */
void lcd_set_clear( uint8_t row );

/*
 * �\���֐�
 *  lcd_set_data �Őݒ肳�ꂽ�f�[�^��{�֐� 1 ��̌Ăяo���� 1 �������\�����Ă����B
 *  ��i�̕\�����I���Ǝ��ɉ��i�̕\�����s��
 */
void lcd_display(void);

/*
 * �\���֐�
 *  �����I�ɕ\�����X�V����s��؂�ւ���B
 *  row: �\�����X�V����s
 */
void lcd_display_row( uint8_t row );


#endif /* LCD_H */

#ifndef LCD_H
#define LCD_H

/************************************************************
 * SC1602 LCD �R���g���[������p���C�u����
 ************************************************************/

#include <stdio.h>

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
void lcd_position( char tx, char ty);

// ���݂̕\���ʒu�� ch ��\������
int lcd_put_ch(char ch);

// ���݂̕\���ʒu���� ch �� 16 �i�\������
int lcd_put_hex2ch(char ch);

// ���݂̕\���ʒu���當�����\������(2��ڂɐ܂�Ԃ��Ȃ�)
void lcd_put_str( char *str );

// fprintf �Ȃǂ� LCD �֏o�͗��p���邽�߂̊֐�
int lcd_put_ch2( char ch, FILE *fp);

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

extern char lcd_dirty[LCD_ROW];

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
 *  len: data �̒���
 */
void lcd_set_data( char *data, int row, int col, size_t len );

/*
 * dirty �t���O�𗧂Ă�֐�
 *  �t���O�𗧂Ă�ꂽ�s�̓f�[�^���X�V����Ă��Ȃ��Ă��ĕ\���̑ΏۂƂȂ�B
 *  �����I�Ɏg����֐��ŁA�ʏ�̓��[�U���g���K�v�͂Ȃ��͂��B
 *  row: �t���O�𗧂Ă�s
 */
void lcd_set_dirty( int row );

/*
 * dirty �t���O�����낷�֐�
 *  �t���O�����낳�ꂽ�s�͕\������f�[�^���c���Ă��Ă��ȍ~�̕\���̃^�C�~���O��
 *  �\�����X�V����Ȃ��Ȃ�B
 *  �����I�Ɏg����֐��ŁA�ʏ�̓��[�U���g���K�v�͂Ȃ��͂��B
 *  row: �t���O�����낷�s
 */
void lcd_clear_dirty( int row );

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
void lcd_display_row( int row );


#endif /* LCD_H */

#ifndef SWITCH_H
#define SWITCH_H

#define SW_OFF 0
#define SW_ON 1

/*
 * �X�C�b�`�̏�Ԃ��擾����֐��B
 *   name: �X�C�b�`�ɕt����C�ӂ̖��O
 *   ���̃}�N�����g������ read_switch_name �Ƃ����֐����錾�����
 */
#define DECLARE_READ_SW_FUNC( name ) \
	int NAME_OF_READ_SW_FUNC(name)( char *out );

/*
 * �X�C�b�`�̏�Ԃ��擾����֐��B
 *   name: �X�C�b�`�ɕt����C�ӂ̖��O
 *   swno: �X�C�b�`�̔ԍ�(lcd.c �Œ�`����)
 *   ���̃}�N�����g������ read_switch_name �Ƃ����֐�����`�����
 * read_swich_name �� I/F
 *   out: �X�C�b�`�̏�Ԃ��i�[�����( SW_ON/SW_OFF )
 *   �Ԓl: �X�C�b�`�̏�Ԃ��O��̖{�֐��Ăяo�����ƕς�����Ƃ��� 1,
 *         �ς���Ă��Ȃ��Ƃ��� 0
 */
#define DEFINE_READ_SW_FUNC( name, swno )  \
	int NAME_OF_READ_SW_FUNC(name)( char *out ){	return sw_get_status( (swno), out); }

#define NAME_OF_READ_SW_FUNC( chr ) read_switch_##chr

/*
 * �X�C�b�`�Ƃ��Ďg���|�[�g�̏�����
 */
void sw_init(void);

/*
 * �X�C�b�`�̏�Ԃ��擾����֐�
 *  ���[�U�͖{�֐����g�킸 DECLARE_READ_SW_FUNC �Ő錾���� read_switch_name �̕��𗘗p���邱��
 */
int sw_get_status( char swno, char *out );

#endif /* SWITCH_H */

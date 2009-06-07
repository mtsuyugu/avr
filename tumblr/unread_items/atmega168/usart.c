#include "macro.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"

/*
 * ref. http://d.hatena.ne.jp/yaneurao/20080713
 */

#define usart_calc_ubrr0( baud ) (F_CPU/16/(baud)-1)


/* sio�ݒ� */
void usart_init()
{
	unsigned int baud = BAUD;
	unsigned int ubrr = usart_calc_ubrr0( baud );
    UBRR0H = (unsigned char)(ubrr>>8);    // �{�[���[�g���8bit
    UBRR0L = (unsigned char)ubrr;        // �{�[���[�g����8bit
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0);;    // ����M����,���荞�݋���
    UCSR0C = (3<<UCSZ00	) ;        // stopbit 1bit , 8bit���M

}

// �t���[��������Ȃ��̂�256 bytes��buffer�����O�ŗp�ӂ���
static volatile char usart_rx_data[256];    // USART�Ŏ�M�����f�[�^�Bring buffer
static volatile int  usart_rx_write;        // ���݂�write�ʒu(usart_rx_data��index)
static          int  usart_rx_read;         // ���݂�read�ʒu(usart_rx_data��index)

// �t���[��������Ȃ��̂�256 bytes��buffer�����O�ŗp�ӂ���
static volatile char usart_tx_data[256];    // USART�ő��M����f�[�^�Bring buffer
static          int  usart_tx_write;        // ���݂�write�ʒu(usart_tx_data��index)
static volatile int  usart_tx_read;         // ���݂�read�ʒu(usart_tx_data��index)

/*********************************************************
 *  ��M
 *********************************************************/

// �f�[�^����M���Ă��邩�̃`�F�b�N�B��M���Ă���Ȃ��0�B
int usart_is_received()
{
    return  (usart_rx_write !=  usart_rx_read) ? 1 : 0;
    // read�ʒu��write�ʒu���قȂ�Ȃ�Ύ�M�f�[�^������͂�
}

// �f�[�^����M����܂őҋ@����
void usart_wait_for_receiving()
{
    while(!usart_is_received())
        ;
}

// ��M�����f�[�^��Ԃ��B��M�����f�[�^���Ȃ��ꍇ�͎�M����܂őҋ@�B
char usart_get_received_chr()
{
    usart_wait_for_receiving();
    return usart_rx_data[usart_rx_read++ & 0xff];
}

// ��M�����f�[�^��Ԃ��B��M�����f�[�^���Ȃ��ꍇ�͑����� return
int usart_get_received_chr_nowait( char *out )
{
	if( usart_is_received() ){
	    *out = usart_rx_data[usart_rx_read++ & 0xff];
		return 1;
	}
	return 0;
}

// ���荞�݂ɂ���M
ISR (USART_RX_vect)
{
    usart_rx_data[usart_rx_write++ & 0xff] = UDR0;    // ��M�f�[�^����M�o�b�t�@�Ɋi�[
}

/*********************************************************
 *  ���M
 *********************************************************/

// ���M�o�b�t�@�Ƀf�[�^������΁A��������1�o�C�g���M���郋�[�`���B
// �����I�Ɏg�p���Ă��邾���Ȃ̂Ń��[�U�[�͌Ăяo���Ȃ��ŁB
void _private_send_char()
{
    if (usart_tx_write != usart_tx_read)
        UDR0 = usart_tx_data[usart_tx_read++];// ���M�o�b�t�@�̃f�[�^�𑗐M
}

// ���荞�݂ɂ�鑗�M
ISR(USART_TX_vect)
{
    _private_send_char();
}


// ���M����������܂őҋ@����
void usart_wait_for_sending()
{
    loop_until_bit_is_set(UCSR0A,UDRE0); // ���M�f�[�^���W�X�^�󂫂܂őҋ@
}

// 1�o�C�g���M
void usart_send_char(int c)
{
    // ���M�o�b�t�@�������ς��Ȃ�҂�
    while(((usart_tx_write + 1) & 0xff) == usart_tx_read)
        ;

    // ���͂Ƃ����ꑗ�M�o�b�t�@�Ƀf�[�^��ςށB
    usart_tx_data[usart_tx_write++] = c;

    // ���M���W�X�^���Z�b�g����Ă��� == ���M�ł����ԁ@�Ȃ�΁A
    // ��x�������M���Ă����B
    if (UCSR0A & (1<<UDRE0))
        _private_send_char();

    // �Ⴆ�Ύ��̂悤�ɑ��M�o�b�t�@�Ƀf�[�^��ς܂���UDR0�ɒ��ڃA�N�Z�X����R�[�h��
    // �悭�Ȃ��B
    // if (UCSR0A & (1<<UDRE0))
    //    UDR0 = c;
    // else
    //    usart_sendData[usart_send_write++] = c;
    // ����́Aelse�傪���s�����u�Ԃ�USART_TX_vect�ɂ�銄�荞�݂�������A
    // usart_send_write == usart_send_read�ł������ꍇ�A����sendChar���Ăяo�����
    // ���̑��M����������܂ł����Őς񂾃f�[�^�����M����Ȃ�����ł���B
}

// ������̑��M
void usart_send_string(char *p)
{
    while(*p)
        usart_send_char(*p++);
}









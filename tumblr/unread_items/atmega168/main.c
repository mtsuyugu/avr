#include "macro.h"

#include <avr/interrupt.h>
#include "lcd.h"
#include "usart.h"
#include "tumblr.h"

DEFINE_READ_SW_FUNC( sw1, 0 );

int main(void)
{

	// ����������
	lcd_init();
	sw_init();
    usart_init();

	tumblr_state_machine_init();
	tumblr_display_init();

    sei(); // �S���荞�݋���

	char d;
	char sw;

    for(;;)
    {
	    // ��M�f�[�^������Ƃ��� ��M�f�[�^�̏���������
		if( usart_get_received_chr_nowait( &d ) ){
			tumblr_state( d );
			continue;
		}

		// ��M�f�[�^���Ȃ��Ƃ��́A�X�C�b�`�̉��������m����
		if( read_switch_sw1( &sw ) && sw == SW_ON ){
			usart_send_string("r");
			tumblr_display_reset();
			continue;
		}

		// ��M�f�[�^���X�C�b�`��������Ă��Ȃ��Ƃ��� LCD �̕\�����X�V����
		lcd_display();
    }
}



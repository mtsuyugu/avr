#include "macro.h"

#include <avr/interrupt.h>
#include "lcd.h"
#include "usart.h"
#include "tumblr.h"

DEFINE_READ_SW_FUNC( sw1, 0 );

int main(void)
{

	// 初期化処理
	lcd_init();
	sw_init();
    usart_init();

	tumblr_state_machine_init();
	tumblr_display_init();

    sei(); // 全割り込み許可

	char d;
	char sw;

    for(;;)
    {
	    // 受信データがあるときは 受信データの処理をする
		if( usart_get_received_chr_nowait( &d ) ){
			tumblr_state( d );
			continue;
		}

		// 受信データがないときは、スイッチの押下を検知する
		if( read_switch_sw1( &sw ) && sw == SW_ON ){
			usart_send_string("r");
			tumblr_display_reset();
			continue;
		}

		// 受信データもスイッチも押されていないときは LCD の表示を更新する
		lcd_display();
    }
}



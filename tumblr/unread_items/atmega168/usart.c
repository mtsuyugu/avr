#include "macro.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"

/*
 * ref. http://d.hatena.ne.jp/yaneurao/20080713
 */

#define usart_calc_ubrr0( baud ) (F_CPU/16/(baud)-1)


/* sio設定 */
void usart_init()
{
	unsigned int baud = BAUD;
	unsigned int ubrr = usart_calc_ubrr0( baud );
    UBRR0H = (unsigned char)(ubrr>>8);    // ボーレート上位8bit
    UBRR0L = (unsigned char)ubrr;        // ボーレート下位8bit
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0);;    // 送受信許可,割り込み許可
    UCSR0C = (3<<UCSZ00	) ;        // stopbit 1bit , 8bit送信

}

// フロー制御をしないので256 bytesのbufferを自前で用意する
static volatile char usart_rx_data[256];    // USARTで受信したデータ。ring buffer
static volatile int  usart_rx_write;        // 現在のwrite位置(usart_rx_dataのindex)
static          int  usart_rx_read;         // 現在のread位置(usart_rx_dataのindex)

// フロー制御をしないので256 bytesのbufferを自前で用意する
static volatile char usart_tx_data[256];    // USARTで送信するデータ。ring buffer
static          int  usart_tx_write;        // 現在のwrite位置(usart_tx_dataのindex)
static volatile int  usart_tx_read;         // 現在のread位置(usart_tx_dataのindex)

/*********************************************************
 *  受信
 *********************************************************/

// データを受信しているかのチェック。受信しているなら非0。
int usart_is_received()
{
    return  (usart_rx_write !=  usart_rx_read) ? 1 : 0;
    // read位置とwrite位置が異なるならば受信データがあるはず
}

// データを受信するまで待機する
void usart_wait_for_receiving()
{
    while(!usart_is_received())
        ;
}

// 受信したデータを返す。受信したデータがない場合は受信するまで待機。
char usart_get_received_chr()
{
    usart_wait_for_receiving();
    return usart_rx_data[usart_rx_read++ & 0xff];
}

// 受信したデータを返す。受信したデータがない場合は即座に return
int usart_get_received_chr_nowait( char *out )
{
	if( usart_is_received() ){
	    *out = usart_rx_data[usart_rx_read++ & 0xff];
		return 1;
	}
	return 0;
}

// 割り込みによる受信
ISR (USART_RX_vect)
{
    usart_rx_data[usart_rx_write++ & 0xff] = UDR0;    // 受信データを受信バッファに格納
}

/*********************************************************
 *  送信
 *********************************************************/

// 送信バッファにデータがあれば、そこから1バイト送信するルーチン。
// 内部的に使用しているだけなのでユーザーは呼び出さないで。
void _private_send_char()
{
    if (usart_tx_write != usart_tx_read)
        UDR0 = usart_tx_data[usart_tx_read++];// 送信バッファのデータを送信
}

// 割り込みによる送信
ISR(USART_TX_vect)
{
    _private_send_char();
}


// 送信が完了するまで待機する
void usart_wait_for_sending()
{
    loop_until_bit_is_set(UCSR0A,UDRE0); // 送信データレジスタ空きまで待機
}

// 1バイト送信
void usart_send_char(int c)
{
    // 送信バッファがいっぱいなら待つ
    while(((usart_tx_write + 1) & 0xff) == usart_tx_read)
        ;

    // 何はともあれ送信バッファにデータを積む。
    usart_tx_data[usart_tx_write++] = c;

    // 送信レジスタがセットされている == 送信できる状態　ならば、
    // 一度だけ送信しておく。
    if (UCSR0A & (1<<UDRE0))
        _private_send_char();

    // 例えば次のように送信バッファにデータを積まずにUDR0に直接アクセスするコードは
    // よくない。
    // if (UCSR0A & (1<<UDRE0))
    //    UDR0 = c;
    // else
    //    usart_sendData[usart_send_write++] = c;
    // これは、else句が実行される瞬間にUSART_TX_vectによる割り込みがかかり、
    // usart_send_write == usart_send_readであった場合、次にsendCharが呼び出されて
    // その送信が完了するまでここで積んだデータが送信されないからである。
}

// 文字列の送信
void usart_send_string(char *p)
{
    while(*p)
        usart_send_char(*p++);
}









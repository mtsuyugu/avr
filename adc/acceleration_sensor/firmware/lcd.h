#ifndef LCD_H
#define LCD_H

/************************************************************
 * SC1602 LCD コントローラ制御用ライブラリ
 ************************************************************/

#include "common.h"

#define LCD_BLANK "                "

/*
 * LCD コントローラを初期化する関数
 */
void lcd_init(void);

/************************************************************
 * 同期型表示関数
 *   LCD コントローラとの通信が終わるまで関数から戻らない表示制御関数群
 *************************************************************/

// 表示位置を tx, ty に移動する
void lcd_position( uint8_t tx, uint8_t ty);

// 現在の表示位置に ch を表示する
void lcd_put_ch(uint8_t ch);

// 現在の表示位置から ch を 16 進表示する
void lcd_put_hex2ch(uint8_t ch);

// 現在の表示位置から文字列を表示する(2列目に折り返さない)
void lcd_put_str( uint8_t *str );

// 表示を全クリア
void lcd_clear_all( void );

// 上段のみ表示クリア
void lcd_clear_upper( void );

// 下段のみ表示クリア
void lcd_clear_lower( void );


/************************************************************
 * 非同期型表示関数
 *   lcd_display を行うまでは LCD コントローラとの通信が発生しない表示制御関数群
 *************************************************************/
#define LCD_UPPER 0  // LCD 上段
#define LCD_LOWER 1  // LCD 下段
#define LCD_ROW 2    // LCD の行数
#define LCD_COL 16   // LCD の列数

extern uint8_t lcd_dirty[LCD_ROW];

/*
 * 表示すべきデータが残っているときに true を返す
 *  lcd_display の内部でも同様のチェックをしているため、
 *  lcd_display を呼ぶ前に本マクロを利用する必要はない。
 */
#define lcd_has_data_to_display() (lcd_dirty[LCD_UPPER] || lcd_dirty[LCD_LOWER])

/*
 * 表示データを設定する関数
 *  data: 表示する文字列
 *  row: 表示する行
 *  col: 表示開始の列
 *  hex8: 16 進で表示する 1バイトの値
 *  hex16: 16 進で表示する 2バイトの値
 *  len: data の長さ
 */
void lcd_set_data( uint8_t *data, uint8_t row, uint8_t col, size_t len );
void lcd_set_hex8( uint8_t hex8, uint8_t row, uint8_t col );
void lcd_set_hex16( uint16_t hex16, uint8_t row, uint8_t col );

/*
 * 表示バッファをクリアする
 *  row: 表示する行
 */
void lcd_set_clear( uint8_t row );

/*
 * 表示関数
 *  lcd_set_data で設定されたデータを本関数 1 回の呼び出しで 1 文字ずつ表示していく。
 *  上段の表示が終わると次に下段の表示を行う
 */
void lcd_display(void);

/*
 * 表示関数
 *  明示的に表示を更新する行を切り替える。
 *  row: 表示を更新する行
 */
void lcd_display_row( uint8_t row );


#endif /* LCD_H */

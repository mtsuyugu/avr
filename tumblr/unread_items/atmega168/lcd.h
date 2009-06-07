#ifndef LCD_H
#define LCD_H

/************************************************************
 * SC1602 LCD コントローラ制御用ライブラリ
 ************************************************************/

#include <stdio.h>

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
void lcd_position( char tx, char ty);

// 現在の表示位置に ch を表示する
int lcd_put_ch(char ch);

// 現在の表示位置から ch を 16 進表示する
int lcd_put_hex2ch(char ch);

// 現在の表示位置から文字列を表示する(2列目に折り返さない)
void lcd_put_str( char *str );

// fprintf などで LCD へ出力利用するための関数
int lcd_put_ch2( char ch, FILE *fp);

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

extern char lcd_dirty[LCD_ROW];

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
 *  len: data の長さ
 */
void lcd_set_data( char *data, int row, int col, size_t len );

/*
 * dirty フラグを立てる関数
 *  フラグを立てられた行はデータが更新されていなくても再表示の対象となる。
 *  内部的に使われる関数で、通常はユーザが使う必要はないはず。
 *  row: フラグを立てる行
 */
void lcd_set_dirty( int row );

/*
 * dirty フラグを下ろす関数
 *  フラグを下ろされた行は表示するデータが残っていても以降の表示のタイミングで
 *  表示が更新されなくなる。
 *  内部的に使われる関数で、通常はユーザが使う必要はないはず。
 *  row: フラグを下ろす行
 */
void lcd_clear_dirty( int row );

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
void lcd_display_row( int row );


#endif /* LCD_H */

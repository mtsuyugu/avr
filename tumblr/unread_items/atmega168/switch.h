#ifndef SWITCH_H
#define SWITCH_H

#define SW_OFF 0
#define SW_ON 1

/*
 * スイッチの状態を取得する関数。
 *   name: スイッチに付ける任意の名前
 *   このマクロを使う事で read_switch_name という関数が宣言される
 */
#define DECLARE_READ_SW_FUNC( name ) \
	int NAME_OF_READ_SW_FUNC(name)( char *out );

/*
 * スイッチの状態を取得する関数。
 *   name: スイッチに付ける任意の名前
 *   swno: スイッチの番号(lcd.c で定義する)
 *   このマクロを使う事で read_switch_name という関数が定義される
 * read_swich_name の I/F
 *   out: スイッチの状態が格納される( SW_ON/SW_OFF )
 *   返値: スイッチの状態が前回の本関数呼び出し時と変わったときに 1,
 *         変わっていないときは 0
 */
#define DEFINE_READ_SW_FUNC( name, swno )  \
	int NAME_OF_READ_SW_FUNC(name)( char *out ){	return sw_get_status( (swno), out); }

#define NAME_OF_READ_SW_FUNC( chr ) read_switch_##chr

/*
 * スイッチとして使うポートの初期化
 */
void sw_init(void);

/*
 * スイッチの状態を取得する関数
 *  ユーザは本関数を使わず DECLARE_READ_SW_FUNC で宣言した read_switch_name の方を利用すること
 */
int sw_get_status( char swno, char *out );

#endif /* SWITCH_H */

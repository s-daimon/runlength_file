#ifndef _func_h
#define _func_h

//文字とその文字数を記録
typedef struct {
	int letter_counter;
    char letter[128];
}node_t;
//バッファ初期化
void init_buf(node_t* buffer);
//バッファのカウンタを１加算
void increase_counter_buf(node_t* buffer);
//バッファのカウンタを１減算
void decrease_counter_buf(node_t* buffer);
//バッファに文字追加
void  add_letter_buf(node_t* buffer, char c);
//デバック用
//バッファの値をすべて表示する
void view_buf(node_t* buffer);

#endif
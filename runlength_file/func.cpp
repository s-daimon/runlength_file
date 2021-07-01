#include <stdio.h>
#include "func.h"
//バッファ初期化
void init_buf(node_t* buffer) {
	buffer->letter_counter = 0;
	for (int i = 0; i < (sizeof(buffer->letter) / sizeof(buffer->letter[0])); i++) {
		buffer->letter[i] = '\0';
	}
	//printf("バッファ初期化");
}
//バッファの文字カウントに１加算
void increase_counter_buf(node_t* buffer) {
	buffer->letter_counter++;
}
//バッファに格納する文字を一つ増やす
void add_letter_buf(node_t* buffer, char c) {
	for (int i = 0; i < (sizeof(buffer->letter) / sizeof(buffer->letter[0])); i++) {
		if (buffer->letter[i] == '\0') {
			buffer->letter[i] = c;
			return;
		}
	}
}
//デバック用
//バッファの値をすべて表示する
void view_buf(node_t* buffer) {
	printf("letter_counter=%d　", buffer->letter_counter);
	printf("letter=");
	for (int i = 0; i < (sizeof(buffer->letter) / sizeof(buffer->letter[0])); i++) {
		if (buffer->letter[i] != '\0')printf("%x",buffer->letter[i]);
	}
	printf("\n");
}
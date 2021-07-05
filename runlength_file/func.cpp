#include <stdio.h>
#include "func.h"
//�o�b�t�@������
void init_buf(node_t* buffer) {
	buffer->letter_counter = 0;
	for (int i = 0; i < (sizeof(buffer->letter) / sizeof(buffer->letter[0])); i++) {
		buffer->letter[i] = -1;
	}
	//printf("�o�b�t�@������");
}
//�o�b�t�@�̕����J�E���g�ɂP���Z
void increase_counter_buf(node_t* buffer) {
	buffer->letter_counter++;
}
//�o�b�t�@�Ɋi�[���镶��������₷
void add_letter_buf(node_t* buffer, char c) {
	for (int i = 0; i < (sizeof(buffer->letter) / sizeof(buffer->letter[0])); i++) {
		if (buffer->letter[i] == -1) {
			buffer->letter[i] = c;
			return;
		}
	}
}

//�f�o�b�N�p
//�o�b�t�@�̒l�����ׂĕ\������
void view_buf(node_t* buffer) {
	printf("letter_counter=%d�@", buffer->letter_counter);
	printf("letter=");
	for (int i = 0; i < (sizeof(buffer->letter) / sizeof(buffer->letter[0])); i++) {
		if (buffer->letter[i] != -1)printf("%x", (unsigned char)buffer->letter[i]);
	}
	printf("\n");
}
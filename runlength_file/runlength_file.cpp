#include <iostream>
#include <vector>
#include "func.h"

int main()
{
	//�t�@�C����
	const char *filename = "TEST-PAC/TEST0.BIN";
	//�t�@�C���ǂݍ���
	FILE* current_fp;
	FILE* next_fp;
	fopen_s(&current_fp, filename, "rb");
	fopen_s(&next_fp,filename,"rb");
	if (current_fp == NULL||next_fp == NULL)
	{
		printf("file�I�[�v���Ɏ��s���܂���!");
		exit(1);
	}
	std::vector<node_t> list;
	node_t buffer;
	buffer.letter_counter = 0;
	buffer.letter[127];
	for (int i = 0; i < (sizeof(buffer.letter) / sizeof(buffer.letter[0])); i++) {
		buffer.letter[i] = '\0';
	}
	//�ЂƂO�̕����ƍ��̕������A�����Ă�����
	bool continuous = false;
	//���̕����Ǝ��̕���
	char current_letter = '0';
	char next_letter;
	//�P����Q�Ƃ���
	next_letter = fgetc(next_fp);
	while (current_letter != EOF) {
		next_letter = fgetc(next_fp);
		current_letter = fgetc(current_fp);
		printf("current = %x�@", current_letter);
		printf("next = %x�@", next_letter);
		if (current_letter == next_letter) {

			if (continuous) {
				increase_counter_buf(&buffer);
			}
			else {
				if (buffer.letter[0] != '\0') {
					list.push_back(buffer);
					init_buf(&buffer);
				}
				add_letter_buf(&buffer, current_letter);
				increase_counter_buf(&buffer);
			}
			continuous = true;
		}
		else {
			if (continuous) {
				increase_counter_buf(&buffer);
				list.push_back(buffer);
				init_buf(&buffer);
			}
			else {
				add_letter_buf(&buffer, current_letter);
				increase_counter_buf(&buffer);
			}
			continuous = false;
		}
		view_buf(&buffer);
	}
	fclose(current_fp);
	fclose(next_fp);
	if (buffer.letter[0] != '\0') list.push_back(buffer);

	//���k��
	printf("���X�g\n");
	for (auto a : list) {
		for (int i = 0; i < (sizeof(a.letter) / sizeof(a.letter[0])); i++) {
			if(a.letter[i]!='\0')printf("%x", a.letter[i]);
		}
		printf(" %d��", a.letter_counter);
		printf("\n");
	}
	return 0;
}

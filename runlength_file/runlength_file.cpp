#include <iostream>
#include <vector>
#include "func.h"

int main()
{	
	//�t�@�C����
	const char *filename = "TEST-PAC/TEST02.BIN";
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
	//���X�g��`
	std::vector<node_t> list;
	node_t buffer;
	buffer.letter_counter =0;
	buffer.letter[127];
	init_buf(&buffer);
	//�ЂƂO�̕����ƍ��̕������A�����Ă�����
	bool continuous = false;
	//���̕����Ǝ��̕���
	int current_letter = -1;
	int next_letter;
	//�P����Q�Ƃ���
	next_letter = fgetc(next_fp);
	//���k���镶���������[�v
	while (next_letter != EOF){
	    next_letter = fgetc(next_fp);
		current_letter = fgetc(current_fp);
		printf("current = %d�@", (unsigned char)current_letter);
		//printf("next = %d�@", (unsigned char)next_letter);
		if (current_letter == next_letter) {

			if (continuous) {
				increase_counter_buf(&buffer);
			}
			else {
				if (buffer.letter[0]!=-1) {
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
				decrease_counter_buf(&buffer);
			}
			continuous = false;
		}
		view_buf(&buffer);
	}
	fclose(current_fp);
	fclose(next_fp);
	if ((buffer.letter_counter) >= 1 ||(buffer.letter_counter) <= -1) list.push_back(buffer);

	//���k��\��
	printf("���X�g\n");
	for (auto a : list) {
		for (int i = 0; i < (sizeof(a.letter) / sizeof(a.letter[0])); i++) {
			//if(a.letter[i]!=-1)
				//printf("%c", (unsigned char)a.letter[i]);
		}
		//printf(" %d��", a.letter_counter);
		printf("\n");
	}
	//���k�����������t�@�C���ɏ�������
	FILE* outputfile;
	fopen_s(&outputfile, "output.bin","wb"); // �t�@�C�����������ݗp�ɃI�[�v��(�J��)
	if (outputfile == NULL) {          // �I�[�v���Ɏ��s�����ꍇ
		printf("cannot open\n");         // �G���[���b�Z�[�W���o����
		exit(1);                         // �ُ�I��
	}
	for (auto a : list) {
		fputc(a.letter_counter, outputfile);
		printf("counter = %d\n", a.letter_counter);
		//fputc(' ', outputfile);
		for (int i = 0; i < (sizeof(a.letter) / sizeof(a.letter[0])); i++) {
			if (a.letter[i] != -1)
				fputc((char)a.letter[i], outputfile);
		}

	}

	fclose(outputfile);
	return 0;
}

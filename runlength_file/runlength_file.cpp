#include <iostream>
#include <vector>
#include "func.h"

int main()
{
	//ファイル名
	const char *filename = "TEST-PAC/TEST0.BIN";
	//ファイル読み込み
	FILE* current_fp;
	FILE* next_fp;
	fopen_s(&current_fp, filename, "rb");
	fopen_s(&next_fp,filename,"rb");
	if (current_fp == NULL||next_fp == NULL)
	{
		printf("fileオープンに失敗しました!");
		exit(1);
	}
	std::vector<node_t> list;
	node_t buffer;
	buffer.letter_counter = 0;
	buffer.letter[127];
	for (int i = 0; i < (sizeof(buffer.letter) / sizeof(buffer.letter[0])); i++) {
		buffer.letter[i] = '\0';
	}
	//ひとつ前の文字と今の文字が連続していたか
	bool continuous = false;
	//今の文字と次の文字
	char current_letter = '0';
	char next_letter;
	//１つ先を参照する
	next_letter = fgetc(next_fp);
	while (current_letter != EOF) {
		next_letter = fgetc(next_fp);
		current_letter = fgetc(current_fp);
		printf("current = %x　", current_letter);
		printf("next = %x　", next_letter);
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

	//圧縮後
	printf("リスト\n");
	for (auto a : list) {
		for (int i = 0; i < (sizeof(a.letter) / sizeof(a.letter[0])); i++) {
			if(a.letter[i]!='\0')printf("%x", a.letter[i]);
		}
		printf(" %d個", a.letter_counter);
		printf("\n");
	}
	return 0;
}

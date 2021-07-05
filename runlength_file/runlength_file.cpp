#include <iostream>
#include <vector>
#include "func.h"

int main()
{	
	//ファイル名
	const char *filename = "TEST-PAC/TEST02.bin";
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
	//リスト定義
	std::vector<node_t> list;
	node_t buffer;
	buffer.letter_counter = 0;
	buffer.letter[127];
	init_buf(&buffer);
	//ひとつ前の文字と今の文字が連続していたか
	bool continuous = false;
	//今の文字と次の文字
	int current_letter = -1;
	int next_letter;
	//１つ先を参照する
	next_letter = fgetc(next_fp);
	//圧縮する文字数分ループ
	while (next_letter != EOF){
	    next_letter = fgetc(next_fp);
		current_letter = fgetc(current_fp);
		//printf("current = %d　", (unsigned char)current_letter);
		//printf("next = %d　", (unsigned char)next_letter);
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
				increase_counter_buf(&buffer);
			}
			continuous = false;
		}
		//view_buf(&buffer);
	}
	fclose(current_fp);
	fclose(next_fp);
	if (buffer.letter_counter >= 1) list.push_back(buffer);

	//圧縮後表示
	printf("リスト\n");
	for (auto a : list) {
		for (int i = 0; i < (sizeof(a.letter) / sizeof(a.letter[0])); i++) {
			//if(a.letter[i]!=-1)
				//printf("%c", (unsigned char)a.letter[i]);
		}
		//printf(" %d個", a.letter_counter);
		printf("\n");
	}
	//圧縮した文字をファイルに書き込む
	FILE* outputfile;
	fopen_s(&outputfile, "output.bin","wb"); // ファイルを書き込み用にオープン(開く)
	if (outputfile == NULL) {          // オープンに失敗した場合
		printf("cannot open\n");         // エラーメッセージを出して
		exit(1);                         // 異常終了
	}
	for (auto a : list) {
		for (int i = 0; i < (sizeof(a.letter) / sizeof(a.letter[0])); i++) {
			if (a.letter[i] != -1)
				fputc((unsigned char)a.letter[i], outputfile);
		}
		fputc((unsigned char)a.letter_counter, outputfile);
		//fputc(' ', outputfile);
	}

	fclose(outputfile);
	return 0;
}

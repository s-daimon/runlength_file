#ifndef _func_h
#define _func_h

//�����Ƃ��̕��������L�^
typedef struct {
	int letter_counter;
    char letter[128];
}node_t;
//�o�b�t�@������
void init_buf(node_t* buffer);
//�o�b�t�@�̃J�E���^���P���Z
void increase_counter_buf(node_t* buffer);
//�o�b�t�@�ɕ����ǉ�
void  add_letter_buf(node_t* buffer, char c);
//�f�o�b�N�p
//�o�b�t�@�̒l�����ׂĕ\������
void view_buf(node_t* buffer);

#endif
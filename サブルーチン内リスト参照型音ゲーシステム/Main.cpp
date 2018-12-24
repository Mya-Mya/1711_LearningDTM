/*
�C���X�g�D�������g�P�F�L�[�{�[�hA
�C���X�g�D�������g�Q�F�L�[�{�[�hJ
�C���X�g�D�������g�O�̓o�b�t�@�[���ɖ�������܂�
*/


#include"DxLib.h"
#include"Main.h"
#include"Keyboard.h"
#pragma warning(disable:4996)
#include<stdio.h>

static GameNow_t GameNow = selecting;

int Choosing=1;//�ȑI��
FILE *Score_handle;//���ʃf�[�^�̃t�@�C���n���h��

struct Score_List_t {
	int clock;//�m�[�g�N���b�N
	int note;//�m�[�g�C���X�g�D�������g
	struct Score_List_t *next;//���̃m�[�g
};
struct Score_List_t *FirstList=NULL;//���X�g�\���̍ŏ�
struct Score_List_t *LastList;//���X�g�\���ǉ����̍�Ɨp�|�C���^
struct Score_List_t *NowList;//�W�I�m�[�g�̃|�C���^
struct Score_List_t *UIList;//UI�\�������邽�߂̍�Ɨp�|�C���^

int TMP_clock;//�ǂݏo�����A�ꎞ�I�Ƀm�[�g�N���b�N�����i�[����
int TMP_note;//�ǂݏo�����A�ꎞ�I�Ƀm�[�g�C���X�g�D�������g�����i�[����

int Now_clock = -180;//���̋Ȑi�s�N���b�N���i�[����
int Good = 0;
int Bad = 0;

struct Score_List_t *ToDeleteList;//�������邽�߂̍�Ɨp�|�C���^
struct Score_List_t *NextDeleteList;//���ɏ������邽�߂̍�Ɨp�|�C���^

int LastClock;//�ȏI�����ɁA���̎|�̕\�����Ԃ̕ێ����ԋL�^�p
#define QUA_CLOCK 5

void Game_mgr() {
	switch (GameNow)
	{
	case selecting:
		Game_select();
		break;
	case buffer:
		Game_buffer();
		break;
	case play:
		Game_play();
		break;
	case result:
		Game_result();
		break;
	}
}

void Game_select() {
	Now_clock = -60;
	if(Keyboard_Get(KEY_INPUT_LEFT)==1){//���{�^����������Ă�����
		Choosing--;
		if (Choosing <= 0) { Choosing = 2; };
	}
	if(Keyboard_Get(KEY_INPUT_RIGHT)==1){//�E�{�^���������ꂽ��
		Choosing++;
		if (Choosing >= 3) { Choosing = 1; };
	}
	if(Keyboard_Get(KEY_INPUT_RETURN)==1){//Enter�������ꂽ��
		Game_change(buffer);
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Z���N�g��ʁA�������܂̑I���Ȃ�%d", Choosing);
}

void Game_buffer() {
	switch (Choosing)//�I���Ȃɉ����ēǂݍ��ރt�@�C����I��
	{
	case 1:
		Score_handle = fopen("1.csv","r");
		break;
	case 2:
		Score_handle = fopen("2.csv", "r");
		break;
	}
	FirstList = NULL;

	while(fscanf(Score_handle, "%d,%d", &TMP_clock, &TMP_note) != EOF) {//���Y���ʃt�@�C���̓ǂݏo���s��EOF�ł͂Ȃ�����
		if((TMP_note)!=0){//�m�[�g�C���X�g�D�������g��0�ȊO��������
			NowList = (Score_List_t*)malloc(sizeof(struct Score_List_t));//�}���b�N�A���ʂ�NowList��
			NowList->clock = TMP_clock, NowList->note = TMP_note, NowList->next = NULL;//�ǂݏo�����m�[�g�f�[�^�����̋�Ԃɑ��

			if(FirstList==NULL){//�������߂Ă̒ǉ���������
				FirstList = NowList;//FirstList�ɂ��̋�Ԃւ̃A�h���X����
				LastList = NowList;
			}
			else {
				LastList->next = NowList;//���O�̒ǉ��ŐV�K�쐬���ꂽ��ԓ���next�ɂ��̋�Ԃւ̃A�h���X����
				LastList = NowList;//����̒ǉ����ւ̂Ȃ�
			}
		}
	}
	fclose(Score_handle);

	NowList = FirstList;
	UIList = FirstList;
	Game_change(play);
}

void Game_change(GameNow_t GameNext) {
	GameNow = GameNext;
}

void Game_play() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Ȑi�s���BGood=%d Bad=%d Now_clock=%d", Good, Bad, Now_clock);

	if (NowList == NULL) {//�������Ȃ��I��������
		DrawFormatString(300, 300, GetColor(255, 255, 255), "�ȏI��");
		if (Now_clock>LastClock + 240) {//�ŏI�̃m�[�g�N���b�N����4�b�o������
			Game_change(result);
			return;
		}
		Now_clock++;
		return;
	}

	Game_UI();//UI�\��

	if (Now_clock < 0) {
		DrawFormatString(0, 30, GetColor(255, 255, 255), "Ready?");
	}
	
	if (Now_clock == 0) {
		//���y�Đ��̃R�}���h
	}


	if (Now_clock > (NowList->clock) - QUA_CLOCK){
		if(Now_clock < (NowList->clock) + QUA_CLOCK){
			DrawFormatString(0, 100, GetColor(255, 200, 200), "�W�I�m�[�g�͈͓�,�m�[�g�C���X�g�D�������g��%d",NowList->note);
			if (Keyboard_Get(KEY_INPUT_A) == 1) { if (NowList->note == 1) { Good++, Game_checkin();} };//�C���X�g�D�������g�P����
			if (Keyboard_Get(KEY_INPUT_J) == 1) { if (NowList->note == 2) { Good++, Game_checkin();} };//�C���X�g�D�������g�Q����
		}
		else {//�͈̓m�[�g�͈͌�
			Bad++;
			Game_checkin();
		}
	}
	else {//�W�I�m�[�g�͈͑O
		if (Keyboard_Get(KEY_INPUT_A) == 1) { Bad++; };//�C���X�g�D�������g�P����
		if (Keyboard_Get(KEY_INPUT_J) == 1) { Bad++; };//�C���X�g�D�������g�Q����
	}
	Now_clock++;
}

void Game_checkin() {
	LastClock = NowList->clock;
	NowList = NowList->next;//�`�F�b�N�C��
}

void Game_result() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "���ʔ��\ esc�őI����ʂ�");
	DrawFormatString(0, 50, GetColor(200, 200, 200), "Good=%d Bad=%d",Good,Bad);
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		
		//���ʃf�[�^�̉��
		ToDeleteList = FirstList;
		NextDeleteList = FirstList;
		while (ToDeleteList != NULL) {
			NextDeleteList = ToDeleteList->next;
			free(ToDeleteList);
			ToDeleteList = NextDeleteList;
		}

		Good = 0, Bad = 0;
		Game_change(selecting);
	}
}

#define ToStrike 650
#define YperClock 6
int UInoteX;

void Game_UI(){
	UIList = FirstList;
	while (UIList != NULL) {
		if (UIList->note == 1) { UInoteX = 400; }
		if (UIList->note == 2) { UInoteX = 650; }//�m�[�g�C���X�g�������g�ɉ����ĕ\��������W�ʒu���w��

		DrawBox(UInoteX, ToStrike + YperClock*Now_clock - YperClock*UIList->clock, UInoteX + 100, ToStrike + YperClock*Now_clock - YperClock*UIList->clock + 20, GetColor(200, 200, 200), TRUE);
		UIList = UIList->next;
	}
	DrawBox(0, ToStrike, 1280, 720,GetColor(160,160,160),TRUE);
	
}
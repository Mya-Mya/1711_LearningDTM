/*���A���^�C���^���Q�[
��{���[��
�C���X�g�D�������g�O�́A�A�{�C�h�m�[�g�E��F���q�ł��B
�L�b�N�̓C���X�g�D�������g�P�A�L�[�{�[�h�`�ƑΉ����܂��B
�X�l�A�̓C���X�g�D�������g�Q�A�L�[�{�[�h�i�ƑΉ����܂��B
�����̓C���X�g�D�������g�R�A�L�[�{�[�h�`�i�ƑΉ����܂��B
*/

#include"DxLib.h"
#include<stdio.h>
#include"Game.h"
#include"keyboard.h"
#include"Root.h"

#define AVOID_NOTE 0
#define KICK 1
#define SNARE 2
#define BOTH 3

extern int TITLE;
extern int CONTENT;
extern int LEAD;

#define Xtitle 0
#define Ytitle 0
#define Ctitle GetColor(255,255,255)
#define Dtitle(in) DrawStringToHandle(Xtitle,Ytitle,in,Ctitle,TITLE)

#define Ccontent GetColor(220,220,220)

#pragma warning(disable:4996)
static GameNow_t GameNow = game_selecting;

#define QUA_CLOCK 5
#define START_CLOCK -180
int Now_clock = START_CLOCK;//���̋Ȑi�s�N���b�N���i�[����
int Good = 0;//�W�I�m�[�g���i
int Bad = 0;//�W�I�m�[�g���i
int LastClock = 0;//�Ō�̃m�[�g�̃N���b�N

void Game_mgr() {
	switch (GameNow)
	{
	case game_selecting:
		Game_select();
		break;
	case game_buffer:
		Game_buffer();
		break;
	case game_play:
		Game_play();
		break;
	case game_result:
		Game_result();
		break;
	}
}

#define MusicNumbers 3
int game_choosing = 1;
void Game_select() {
	Dtitle("���A���^�C���^���Q�[��");
	DrawStringToHandle(50, 100, "�����ł́ADAW�̃��A���^�C���^���̋@�\���������Ă��炤���߂ɁABGM�̐i�s��\n�Ƃ��Ƀh����(�L�b�N�E�X�l�A)��ł�����ł��炢�܂��BA�ŃL�b�N���AJ�ŃX�l�A\n��ł����݂܂��B�����̃Y���̓N�I���^�C�Y�ɏC�����Ă��炦�܂����A���܂�ɂ�\n�Y�������Ă���Ǝ��_�ƂȂ�܂��B�u�~���[�g/�\���@�\�v�ɂăh�����̃��Y����\n�m�F���邱�Ƃ��������߂��܂��BBGM��I��Enter�������ĊJ�n���܂��B", Ccontent, CONTENT);

	//�L�[�{�[�h����
	if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
		game_choosing++;
		if (game_choosing > MusicNumbers) { game_choosing = MusicNumbers; }
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
		game_choosing--;
		if (game_choosing < 1) { game_choosing = 1; }
	}
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		RootChange(Menu);
		return;
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		Game_change(game_buffer);
	}
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
		RootChange(Mix);
	}
	
	//���̑��̕\��
	DrawStringToHandle(200, 690, "�����őI�� Enter�ōĐ� Space�Ń~���[�g/�\���@�\�� Esc�Ń^�C�g����ʂ�", Ccontent, LEAD);
	DrawFormatStringToHandle(470, 450, GetColor(255, 100, 100), CONTENT, "BGM%d��I�𒆂ł�", game_choosing);
}

int Game_SoundHandles[7] = { 0 };//���ꂼ��̃p�[�g�̃T�E���h�n���h��
int KickSoundHandle, SnareSoundHandle, BothSoundHandle;//�C���X�g�D�������g�̃T�E���h���Đ�����
FILE *Score_handle;//���ʃf�[�^�̃t�@�C���n���h��

struct Score_List_t {//�e�m�[�g�̃f�[�^
	int clock;//�e�m�[�g�̃N���b�N
	int note;//�e�m�[�g�̃C���X�g�D�������g
	struct Score_List_t *next;//���̃m�[�g
};
struct Score_List_t *FirstList = NULL;//���X�g�\���̍ŏ�
struct Score_List_t *LastList;//���X�g�\���ǉ����̍�Ɨp�|�C���^
struct Score_List_t *NowList;//�W�I�m�[�g�̃|�C���^
struct Score_List_t *UIList;//UI�\�������邽�߂̍�Ɨp�|�C���^

int READ_clock;//�ǂݏo�����A�ꎞ�I�Ƀm�[�g�N���b�N�����i�[����
int READ_note;//�ǂݏo�����A�ꎞ�I�Ƀm�[�g�C���X�g�D�������g�����i�[����

void Game_buffer() {
	InitSoundMem();//��������̑S�ẴT�E���h������
	//���y�t�@�C���ƕ��ʃf�[�^�̃t�@�C�����w��
	switch (game_choosing) {
	case 1:
		Game_SoundHandles[0] = LoadSoundMem("BGM1/Melody.wav");
		Game_SoundHandles[1] = LoadSoundMem("BGM1/Kawa_Drum.wav");
		Game_SoundHandles[2] = LoadSoundMem("BGM1/Kinzoku_Drum.wav");
		Game_SoundHandles[3] = LoadSoundMem("BGM1/Bass.wav");
		Game_SoundHandles[4] = LoadSoundMem("BGM1/Guitar.wav");
		Game_SoundHandles[5] = LoadSoundMem("BGM1/Piano.wav");
		Game_SoundHandles[6] = LoadSoundMem("BGM1/Other.wav");
		KickSoundHandle = LoadSoundMem("BGM1/Kick.wav");
		SnareSoundHandle = LoadSoundMem("BGM1/Snare.wav");
		BothSoundHandle = LoadSoundMem("BGM1/Both.wav");
		Score_handle = fopen("BGM1/Score.csv","r");
		break;
	case 2:
		Game_SoundHandles[0] = LoadSoundMem("BGM2/Melody.wav");
		Game_SoundHandles[1] = LoadSoundMem("BGM2/Kawa_Drum.wav");
		Game_SoundHandles[2] = LoadSoundMem("BGM2/Kinzoku_Drum.wav");
		Game_SoundHandles[3] = LoadSoundMem("BGM2/Bass.wav");
		Game_SoundHandles[4] = LoadSoundMem("BGM2/Guitar.wav");
		Game_SoundHandles[5] = LoadSoundMem("BGM2/Piano.wav");
		Game_SoundHandles[6] = LoadSoundMem("BGM2/Other.wav");
		KickSoundHandle = LoadSoundMem("BGM2/Kick.wav");
		SnareSoundHandle = LoadSoundMem("BGM2/Snare.wav");
		BothSoundHandle = LoadSoundMem("BGM2/Both.wav");
		Score_handle = fopen("BGM2/Score.csv", "r");
		break;
	case 3:
		Game_SoundHandles[0] = LoadSoundMem("BGM3/Melody.wav");
		Game_SoundHandles[1] = LoadSoundMem("BGM3/Kawa_Drum.wav");
		Game_SoundHandles[2] = LoadSoundMem("BGM3/Kinzoku_Drum.wav");
		Game_SoundHandles[3] = LoadSoundMem("BGM3/Bass.wav");
		Game_SoundHandles[4] = LoadSoundMem("BGM3/Guitar.wav");
		Game_SoundHandles[5] = LoadSoundMem("BGM3/Piano.wav");
		Game_SoundHandles[6] = LoadSoundMem("BGM3/Other.wav");
		KickSoundHandle = LoadSoundMem("BGM3/Kick.wav");
		SnareSoundHandle = LoadSoundMem("BGM3/Snare.wav");
		BothSoundHandle = LoadSoundMem("BGM3/Both.wav");
		Score_handle = fopen("BGM3/Score.csv", "r");
		break;
	}

	//���ʃf�[�^�t�@�C������ǂݏo���e�m�[�g�f�[�^�̃��X�g���\������
	while(fscanf(Score_handle,"%d,%d",&READ_clock,&READ_note)!=EOF){//�m�[�g��1���ǂݏo��
		if (READ_note != AVOID_NOTE) {//���̃C���X�g�D�������g����F���q�łȂ�������
			NowList = (Score_List_t*)malloc(sizeof(struct Score_List_t));//���I�������m��
			NowList->clock = READ_clock, NowList->note = READ_note, NowList->next = NULL;//�V�K��ԏ�Ƀm�[�g�����R�s�[
			if (FirstList == NULL) {//�������߂Ă̒ǉ���������
				FirstList = NowList;//FirstList�ɂ��̋�Ԃւ̃A�h���X����
				LastList = NowList;
			}
			else {
				LastList->next = NowList;//���O�̒ǉ��ŐV�K�쐬���ꂽ��ԓ���next�ɂ��̋�Ԃւ̃A�h���X����
				LastList = NowList;//����̒ǉ����ւ̂Ȃ�
			}
		}
	}

	//�Q�[���i�s���̕ϐ��̏�����
	NowList = FirstList;
	UIList = FirstList;
	Game_change(game_play);
}

#define Game_PLAY_MESSAGE(x,y,in) DrawStringToHandle(x,y,in,Ccontent,CONTENT)

//���ʃf�[�^�̃`�F�b�N�C�����s��
void Game_checkin() {
	LastClock = NowList->clock;
	NowList = NowList->next;
}

//���_�Ɋւ���}�N���E����
#define GOOD 1
#define BAD 0
#define DefaultPointNotifyClock 6
int GoodNotify = DefaultPointNotifyClock;
int BadNotify = DefaultPointNotifyClock;
void PointChange(int Which) {
	switch (Which) {
	case GOOD:
		Good++;
		GoodNotify=0;
		break;
	case BAD:
		Bad++;
		BadNotify=0;
		break;
	}
}

//���ʂ�\������
#define ToStrike 650
#define YperClock 8
void Game_UI_Notedraw(int UInoteX) {
	DrawBox((UInoteX), (ToStrike + YperClock*Now_clock - YperClock*UIList->clock)-6, (UInoteX + 180),( ToStrike + YperClock*Now_clock - YperClock*UIList->clock)+4, GetColor(121, 207, 114), TRUE);
}
void Game_UI_Boxdraw(int color) {
	DrawBox(0, ToStrike, 1280, 720, color, TRUE);
}

void Game_UI() {
	UIList = FirstList;
	while (UIList != NULL) {
		if (UIList->note == KICK) { Game_UI_Notedraw(420); }
		if (UIList->note == SNARE) { Game_UI_Notedraw(670); }
		if (UIList->note == BOTH) { Game_UI_Notedraw(420), Game_UI_Notedraw(670); }

		UIList = UIList->next;
	}

	Game_UI_Boxdraw(GetColor(60, 60, 60));
	//���_UI�ʒm
	if (GoodNotify != DefaultPointNotifyClock){
		BadNotify = DefaultPointNotifyClock;
		Game_UI_Boxdraw(GetColor(136, 200, 184));
		GoodNotify++;
	}
	if (BadNotify != DefaultPointNotifyClock) {
		GoodNotify = DefaultPointNotifyClock;
		Game_UI_Boxdraw(GetColor(200, 135, 136));
		BadNotify++;
	}

	DrawFormatStringToHandle(50, 670, GetColor(255, 255, 255), CONTENT, "Good = %d  Bad = %d", Good, Bad);
	Game_PLAY_MESSAGE(500, 670, "A");//450+50
	Game_PLAY_MESSAGE(750, 670, "J");//700+50
}


//�C���X�g�D�������g�̃T�E���h���Đ�����
void Game_InstrumentsSound() {
	if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) == 1) PlaySoundMem(BothSoundHandle, DX_PLAYTYPE_BACK, TRUE);
	if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) != 1) PlaySoundMem(KickSoundHandle, DX_PLAYTYPE_BACK, TRUE);
	if (Keyboard_Get(KEY_INPUT_A) != 1 && Keyboard_Get(KEY_INPUT_J) == 1) PlaySoundMem(SnareSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}


//���~�̍ۂ̂��m�点�p�ϐ�
#define DefaultStopClock 60
int StopClock = DefaultStopClock;

//�i�s���C�����[�`��
void Game_play() {
	DrawFormatStringToHandle(0, 0, Ccontent, CONTENT, "BGM%d���Đ����@Esc�Œ��~", game_choosing);

	Game_InstrumentsSound();//�C���X�g�D�������g�̃T�E���h���Đ�����
	Game_UI();

	//�Ȃ̖��[����������
	if(NowList==NULL){
		Game_PLAY_MESSAGE(550, 350, "�I��");
		if (Now_clock>LastClock + 240) {//�ŏI�̃m�[�g�N���b�N����4�b�o������
			Game_change(game_result);
			return;
		}
		Now_clock++;
		return;
	}

	//�ҋ@���̃��b�Z�[�W
	if (Now_clock < 0) {
		Game_PLAY_MESSAGE(550,350, "Ready ?");
	}

	//���y�t�@�C���Đ��J�n
	if (Now_clock == 0) {
		for (int i = 0; i < 7; i++) {
			if (i == 1) { i = 2; }//��h�����̏���
			PlaySoundMem(Game_SoundHandles[i], DX_PLAYTYPE_BACK, TRUE);
			ChangeVolumeSoundMem(220, Game_SoundHandles[i]);
		}
	}

	//����
	if (Now_clock >(NowList->clock) - QUA_CLOCK) {
		if (Now_clock < (NowList->clock) + QUA_CLOCK) {
			if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) == 1) { if (NowList->note == BOTH) { PointChange(GOOD), Game_checkin(); } }//�C���X�g�D�������g�R����
			if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) != 1) { if (NowList->note == KICK) { PointChange(GOOD), Game_checkin(); } };//�C���X�g�D�������g�P����
			if (Keyboard_Get(KEY_INPUT_A) != 1 && Keyboard_Get(KEY_INPUT_J) == 1) { if (NowList->note == SNARE) { PointChange(GOOD), Game_checkin(); } };//�C���X�g�D�������g�Q����
		}
		else {//�͈̓m�[�g�͈͌�
			PointChange(BAD);
			Game_checkin();
		}
	}
	else {//�W�I�m�[�g�͈͑O
		if (Keyboard_Get(KEY_INPUT_A) == 1) { PointChange(BAD); };//�C���X�g�D�������g�P����
		if (Keyboard_Get(KEY_INPUT_J) == 1) { PointChange(BAD); };//�C���X�g�D�������g�Q����
	}

	//���~
	if (StopClock != DefaultStopClock) {
		Game_PLAY_MESSAGE(550, 350, "���~���܂�");
		StopClock++;
		if (StopClock == DefaultStopClock-1) StopClock = DefaultStopClock, Game_change(game_result);
	}
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		StopClock=0;//���~�ҋ@�����̃g���K�[�����
	}

	//���[������
	if (-70<Now_clock && Now_clock < 150) {
		DrawLine(350, ToStrike-2, 960, ToStrike-2, GetColor(255, 255, 100));
		Game_PLAY_MESSAGE(240, 610, "���̋��E���ɗΐF�̉����������Ă����u�Ԃ�A�܂���J�������܂��B");
	}

	//�Ȑi�s
	Now_clock++;
}

void Game_change(GameNow_t GameNext) {
	GameNow = GameNext;
}


//���ʂ̕\������у��Z�b�g
struct Score_List_t *ToDeleteList;
struct Score_List_t *NextDeleteList;
void Game_result() {
	for (int i = 0; i < 7; i++) {
		StopSoundMem(Game_SoundHandles[i]);
	}
	DrawFormatStringToHandle(0, 150, Ccontent, CONTENT, "�X�R�A��Good = %d  Bad = %d �ł����B\n�v���C���Ē������肪�Ƃ��������܂����B Esc�őI����ʂ֖߂�܂��B", Good, Bad);
	void Game_result_comment();

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		//���ʃf�[�^�̉��
		ToDeleteList = FirstList;
		NextDeleteList = FirstList;
		while (ToDeleteList != NULL) {
			NextDeleteList = ToDeleteList->next;
			free(ToDeleteList);
			ToDeleteList = NextDeleteList;
		}

		FirstList = NULL;
		Now_clock = START_CLOCK;//�Q�[���i�s�N���b�N�����Z�b�g
		Good = 0, Bad = 0;
		Game_change(game_selecting);
	}
}

void Game_result_comment() {
	char Message[128];
	DrawFormatStringToHandle(30, 400, GetColor(200, 200, 200), CONTENT, "%s", Message);
}
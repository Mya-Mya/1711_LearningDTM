#include"Mix.h"
#include"DxLib.h"
#include"Keyboard.h"
#include"Root.h"
#pragma warning(disable:4993)

static MixNow_t MixNow = intro;

extern int TITLE;
extern int CONTENT;
extern int LEAD;

#define Xtitle 0
#define Ytitle 0
#define Ctitle GetColor(255,255,255)
#define Dtitle(in) DrawStringToHandle(Xtitle,Ytitle,in,Ctitle,TITLE)

#define Ccontent GetColor(220,220,220)

void Mix_mgr() {
	switch (MixNow) 
	{
	case intro:
		Mix_intro();
		break;
	case buffer:
		Mix_buffer();
		break;
	case play:
		Mix_play();
		break;
	}
}

void Mix_change(MixNow_t MixNext) {
	MixNow = MixNext;
}

/*���y�t�@�C���n���h��
�O�����f�B
�P��h����
�Q�����h����
�R�x�[�X
�S�M�^�[
�T�s�A�m
�U�p�b�h���̂��̑�*/
int Mix_SoundHandles[7] = { 0 };

#define MusicNumbers 3
int mix_choosing=1;

//���ʂɊւ���}�N���ƕϐ�
#define MIX_ON 255
#define MIX_OFF 0
int SoundVolumes[7] = { MIX_ON,MIX_ON,MIX_ON,MIX_ON,MIX_ON,MIX_ON,MIX_ON };

void Mix_intro() {
	Dtitle("�~���[�g/�\���@�\");
	DrawStringToHandle(50, 100, "�����ł́ADAW�̃~���[�g/�\���@�\���������Ă��炤���߂ɁA�F�����BGM��\n�Đ����ɔC�ӂ̊y��̉���ON / OFF�̐؂�ւ������āA�~���[�g / �\���@�\��\n�ǂ̂悤�ɕ��������ɉe�����邩���m���߂��������B\nBGM��I��Enter�������čĐ����܂��B", Ccontent, CONTENT);

	//�L�[�{�[�h����
	if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
		mix_choosing++;
		if (mix_choosing > MusicNumbers) { mix_choosing = MusicNumbers; }
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
		mix_choosing--;
		if (mix_choosing < 1) { mix_choosing = 1; }
	}
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		RootChange(Menu);
		return;
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		Mix_change(buffer);
	}
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
		RootChange(Game);
	}
	//���̑��̕\��
	DrawStringToHandle(200, 690, "�����őI�� Enter�ōĐ� Space�ŃQ�[���� Esc->�^�C�g����ʂ�", Ccontent, LEAD);
	DrawFormatStringToHandle(470, 350, GetColor(255, 100, 100), CONTENT, "BGM%d��I�𒆂ł�", mix_choosing);
};

void Mix_buffer() {
	InitSoundMem();//��������̑S�ẴT�E���h������
	switch (mix_choosing) {
	case 1:
		Mix_SoundHandles[0] = LoadSoundMem("BGM1/Melody.wav");
		Mix_SoundHandles[1] = LoadSoundMem("BGM1/Kawa_Drum.wav");
		Mix_SoundHandles[2] = LoadSoundMem("BGM1/Kinzoku_Drum.wav");
		Mix_SoundHandles[3] = LoadSoundMem("BGM1/Bass.wav");
		Mix_SoundHandles[4] = LoadSoundMem("BGM1/Guitar.wav");
		Mix_SoundHandles[5] = LoadSoundMem("BGM1/Piano.wav");
		Mix_SoundHandles[6] = LoadSoundMem("BGM1/Other.wav");
		break;
	case 2:
		Mix_SoundHandles[0] = LoadSoundMem("BGM2/Melody.wav");
		Mix_SoundHandles[1] = LoadSoundMem("BGM2/Kawa_Drum.wav");
		Mix_SoundHandles[2] = LoadSoundMem("BGM2/Kinzoku_Drum.wav");
		Mix_SoundHandles[3] = LoadSoundMem("BGM2/Bass.wav");
		Mix_SoundHandles[4] = LoadSoundMem("BGM2/Guitar.wav");
		Mix_SoundHandles[5] = LoadSoundMem("BGM2/Piano.wav");
		Mix_SoundHandles[6] = LoadSoundMem("BGM2/Other.wav");
		break;
	case 3:
		Mix_SoundHandles[0] = LoadSoundMem("BGM3/Melody.wav");
		Mix_SoundHandles[1] = LoadSoundMem("BGM3/Kawa_Drum.wav");
		Mix_SoundHandles[2] = LoadSoundMem("BGM3/Kinzoku_Drum.wav");
		Mix_SoundHandles[3] = LoadSoundMem("BGM3/Bass.wav");
		Mix_SoundHandles[4] = LoadSoundMem("BGM3/Guitar.wav");
		Mix_SoundHandles[5] = LoadSoundMem("BGM3/Piano.wav");
		Mix_SoundHandles[6] = LoadSoundMem("BGM3/Other.wav");
		break;
	}
	//�Đ��Ɖ��ʏ����ݒ�
	for (int i = 0; i < 7; i++) {
		PlaySoundMem(Mix_SoundHandles[i], DX_PLAYTYPE_BACK, TRUE);
		SoundVolumes[i] = MIX_ON;
		ChangeVolumeSoundMem(SoundVolumes[i], Mix_SoundHandles[i]);
	}
	Mix_change(play);
}

#define MIX_PLAY_INSTRUMENTS(x,y,in) DrawStringToHandle(x,y,in,Ccontent,CONTENT)
#define MIX_PLAY_MESSAGE(x,y,in) DrawStringToHandle(x,y,in,GetColor(230,230,230),CONTENT)
#define MIX_PLAY_SWITCH(x,y,in) DrawStringToHandle(x,y,in,GetColor(200,150,150),CONTENT)

//�v���C����UI���W�Ɋւ���}�N��
#define Ydistance 70 
#define Yroot 150

/*���y�t�@�C���n���h��
�O�����f�B
�P��h����
�Q�����h����
�R�x�[�X
�S�M�^�[
�T�s�A�m
�U�p�b�h���̂��̑�*/
void Mix_play() {
	//���ʐ���
	if (Keyboard_Get(KEY_INPUT_A) == 1) {
		if (SoundVolumes[0] == MIX_ON) {
			SoundVolumes[0] = MIX_OFF;
		}
		else {
			SoundVolumes[0] = MIX_ON;
		}
		ChangeVolumeSoundMem(SoundVolumes[0], Mix_SoundHandles[0]);
	}
	if (Keyboard_Get(KEY_INPUT_S) == 1) {
		if (SoundVolumes[1] == MIX_ON) {
			SoundVolumes[1] = MIX_OFF;
		}
		else {
			SoundVolumes[1] = MIX_ON;
		}
		ChangeVolumeSoundMem(SoundVolumes[1], Mix_SoundHandles[1]);
	}
	if (Keyboard_Get(KEY_INPUT_D) == 1) {
		if (SoundVolumes[2] == MIX_ON) {
			SoundVolumes[2] = MIX_OFF;
		}
		else {
			SoundVolumes[2] = MIX_ON;
		}
		ChangeVolumeSoundMem(SoundVolumes[2], Mix_SoundHandles[2]);
	}
	if (Keyboard_Get(KEY_INPUT_F) == 1) {
		if (SoundVolumes[3] == MIX_ON) {
			SoundVolumes[3] = MIX_OFF;
		}
		else {
			SoundVolumes[3] = MIX_ON;
		}
		ChangeVolumeSoundMem(SoundVolumes[3], Mix_SoundHandles[3]);
	}
	if (Keyboard_Get(KEY_INPUT_G) == 1) {
		if (SoundVolumes[4] == MIX_ON) {
			SoundVolumes[4] = MIX_OFF;
		}
		else {
			SoundVolumes[4] = MIX_ON;
		}
		ChangeVolumeSoundMem(SoundVolumes[4], Mix_SoundHandles[4]);
	}
	if (Keyboard_Get(KEY_INPUT_H) == 1) {
		if (SoundVolumes[5] == MIX_ON) {
			SoundVolumes[5] = MIX_OFF;
		}
		else {
			SoundVolumes[5] = MIX_ON;
		}
		ChangeVolumeSoundMem(SoundVolumes[5], Mix_SoundHandles[5]);
	}
	if (Keyboard_Get(KEY_INPUT_J) == 1) {
		if (SoundVolumes[6] == MIX_ON) {
			SoundVolumes[6] = MIX_OFF;
		}
		else {
			SoundVolumes[6] = MIX_ON;
		}
		ChangeVolumeSoundMem(SoundVolumes[6], Mix_SoundHandles[6]);
	}

	//�L�[�{�[�h����
	{if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		for (int i = 0; i < 7; i++) {
			StopSoundMem(Mix_SoundHandles[i]);
		}
		Mix_change(intro);
	}}
	//UI�\��
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), TITLE, "BGM%d���Đ���", mix_choosing);
	MIX_PLAY_MESSAGE(10, 70, "���ꂼ�ꌈ�߂�ꂽ�L�[�ŔC�ӂ̊y��̉���ON/OFF�̐؂�ւ����ł��܂��BESC�Ŗ߂�B");
	MIX_PLAY_INSTRUMENTS(100, Yroot+Ydistance*0, "(A)�����f�B");
	MIX_PLAY_INSTRUMENTS(100, Yroot+Ydistance*1, "(S)�h����(�L�b�N�E�X�l�A)");
	MIX_PLAY_INSTRUMENTS(100, Yroot+Ydistance*2, "(D)�h����(�����n)");
	MIX_PLAY_INSTRUMENTS(100, Yroot+Ydistance*3, "(F)�x�[�X");
	MIX_PLAY_INSTRUMENTS(100, Yroot+Ydistance*4, "(G)�M�^�[�Ȃ�");
	MIX_PLAY_INSTRUMENTS(100, Yroot+Ydistance*5, "(H)�s�A�m�Ȃ�");
	MIX_PLAY_INSTRUMENTS(100, Yroot+Ydistance*6, "(J)���̑�");

	for (int i = 0; i < 7; i++) {
		if (SoundVolumes[i] == MIX_ON) { 
			MIX_PLAY_SWITCH(750, Yroot + Ydistance*i, "ON");
		}
		else {
			MIX_PLAY_SWITCH(800, Yroot + Ydistance*i, "OFF");
		}
	}

};
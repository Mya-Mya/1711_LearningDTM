#include<dshow.h>
#include"Root.h"
#include"Tutorial.h"
#include"Keyboard.h"
#include"DxLib.h"
#include <stdlib.h>
#include<Windows.h>

//�i�s�p�ϐ�
int Tutorial_page = 1;
int Escape_time = 0;

//�摜�n���h��
int tutorial_PicsBuf_First_time = 0;
int Tutorial_PicHandle01, Tutorial_PicHandle03, Tutorial_PicHandle05, Tutorial_PicHandle07, Tutorial_PicHandle09, Tutorial_PicHandle11, Tutorial_PicHandle13, Tutorial_PicHandle15, Tutorial_PicHandle17, Tutorial_PicHandle19, Tutorial_PicHandle21;

extern int TITLE;
extern int CONTENT;
extern int LEAD;

#define Xtitle 0
#define Ytitle 20
#define Ctitle GetColor(255,255,255)
#define Dtitle(in) DrawStringToHandle(Xtitle,Ytitle,in,Ctitle,TITLE)

#define Xcontent 50
#define Ycontent 250
#define Ccontent GetColor(220,220,220)
#define Dcontent(in) DrawStringToHandle(Xcontent,Ycontent,in,Ccontent,CONTENT)

#define Tmovie DrawStringToHandle(0,530,"Space�œ��������",GetColor(255,150,150),CONTENT);

//�������̗͂��ɑ}������p�̓��߉摜�𓊉�
void ExplainingDrawGraph(int Handle) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
	DrawGraph(0, 0, Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Tutorial_main() {
	
	if(tutorial_PicsBuf_First_time==0){//���߂ẴA�N�Z�X��������
		Tutorial_buffer();
		return;
	}
	//���C���R���e���c�̕\��
	switch(Tutorial_page) {
	case 1:
		//��{�I�ɂ�M1�Ɠ��������A�A���O����ς���
		DrawGraph(0, 0, Tutorial_PicHandle01,TRUE);
		Dtitle("�`���[�g���A��");
		break; 
	case 2:
		ExplainingDrawGraph(Tutorial_PicHandle01);
		Dtitle("DTM���ĉ��H");
		Dcontent("PC���g���ĉ��y��������邱�Ƃ�DTM(DeskTop Music�E�f�X�N�g�b�v�~���[�W�b�N)\n�ƌĂт܂��B�A�[�e�B�X�g�̃v���f���[�T�[��T�E���h�N���G�C�^�[����\n�v�����s���Ă��āA�ȒP�ɍ�Ȃ�ҋȂ��ł��܂��B");
		break;
	case 3:
		//Studio One�̃z�[�����
		DrawGraph(0, 0, Tutorial_PicHandle03, TRUE);
		break;
	case 4:
		ExplainingDrawGraph(Tutorial_PicHandle03);
		Dtitle("DTM��p�\�t�g�E�F�A�uDAW�v");
		Dcontent("���y���������\�t�g�E�F�A����ʓI�ɁuDAW�v�Ƃ����܂��B�����̂��̂���A\n�L���ȃA�C�h���O���[�v�̃v���f���[�T�[���g���Ă���悤�ȍ����Ȃ��̂܂�\n�������񂠂�܂��B���̉摜�́A�����g���Ă���Pronouns�Ђ́uStudio One�v\n�Ƃ���DAW�̉�ʂł��B���̃y�[�W����́AStudio One�̎��ۂ̉�ʂƋ��ɁA\nDAW���ł��邱�ƁADTM�łł��邱�Ƃ�������܂��B");
		break;
	case 5:
		//�C���X�g�D�������g�ꗗ�\�̃u���E�Y���
		DrawGraph(0, 0, Tutorial_PicHandle05, TRUE);
		break;
	case 6:
		ExplainingDrawGraph(Tutorial_PicHandle05);
		Dtitle("�F�X�Ȋy������� ");
		Dcontent("DAW���ɂ́u�\�t�g�E�F�A�����v�Ƃ����A���ۂ̃V���Z�T�C�U�[��s�A�m�A�M�^�[�A\n�h�����Ȃǂ̗l�X�Ȋy��̉����V�~�����[�g����v���O�������g�ݍ��܂�Ă��܂��B\nStudio One�ł̓\�t�g�E�F�A�����̃v���O�������u�C���X�g�D�������g�v��\n�Ă΂�Ă���̂ŁA�Ȍセ���ĂԂ��Ƃɂ��܂��B�����ł́A�V���Z�T�C�U�[��\n�C���X�g�D�������g���N�����A<�h>�̉���炵�Ă݂܂����B");
		Tmovie
		break;
	case 7:
		//�ł����܂ꂽ�s�A�m���[��
		DrawGraph(0, 0, Tutorial_PicHandle07, TRUE);
		break;
	case 8:
		ExplainingDrawGraph(Tutorial_PicHandle07);
		Dtitle("���t���Ă��炤");
		Dcontent("�N�������C���X�g�D�������g�ɁA�������t���Ă��炢�܂��B�u�s�A�m���[���v\n�ƌĂ΂�邱�̕\�́A�c�������̍����ŁA���������Ԃ������Ă��܂��B�����ł́A\n5���ߖڂ̓���<��>��4��������z�u���܂����B���̂悤�ɁA������z�u���邱�Ƃ�\n�u�ł����ށv�Ƃ����܂��B");
		Tmovie
		break;
	case 9:
		//�䂤�₯���₯�̃m�[�g��ł����񂾃s�A�m���[��
		DrawGraph(0, 0, Tutorial_PicHandle09, TRUE);
		break;
	case 10:
		ExplainingDrawGraph(Tutorial_PicHandle09);
		Dtitle("���t���Ă��炤(2)");
		Dcontent("�u�䂤�₯���₯�v�Ƃ������w�y�Ȃ̃����f�B��ł����݁A�Đ��{�^����������\n���t���Ă��炢�܂����B�V���Z�T�C�U�[�̉��Łu�䂤�₯���₯�v������܂����B");
		Tmovie
		break;
	case 11:
		//�s�A�m�g���b�N�ƃV���Z�g���b�N�̕����s�A�m���[��
		DrawGraph(0, 0, Tutorial_PicHandle11, TRUE);
		break;
	case 12:
		ExplainingDrawGraph(Tutorial_PicHandle11);
		Dtitle("���t��t������");
		Dcontent("���Ƀs�A�m�̉��Ŕ��t��t�������Ă��炨���Ǝv���܂��B�ǉ��Ńs�A�m��\n�C���X�g�D�������g���N�����āA���t��ł����݂܂����B�Ԃ������������f�B�A\n�������������t�ł��B");
		Tmovie
		break;
	case 13:
		//�����̃g���b�N
		DrawGraph(0, 0, Tutorial_PicHandle13, TRUE);
		break;
	case 14:
		ExplainingDrawGraph(Tutorial_PicHandle13);
		Dtitle("����ɐF�X�Ȋy���t������");
		Dcontent("����Ɋy���t�������č��؂ɂ��Ă݂܂����B�ł��A���܂��Y��ɕ������܂���B\n���ꂼ��̊y�킪���a���Ă��Ȃ�����ł��B�����Y��ɕ����������邽�߂�\n���H���K�v�Ȃ̂ł��B");
		Tmovie
		break;
	case 15:
		//�C�R���C�U�[�E�B���h�E�A�~�b�N�X�E�B���h�E
		DrawGraph(0, 0, Tutorial_PicHandle15, TRUE);
		break;
	case 16:
		ExplainingDrawGraph(Tutorial_PicHandle15);
		Dtitle("�~�b�N�X/�}�X�^�����O");
		Dcontent("���ꂼ��̉������H���邱�Ƃ��u�~�b�N�X�v�܂��́u�}�X�^�����O�v�Ƃ����܂��B\n���ꂼ��̊y��̉��𐮂��đS�̓I���Y��ɕ�������悤�ɂ��܂��B\n���ʂȊy�킪�W�܂��Ĕ������n�[���j�[�ƂȂ�܂����B");
		Tmovie
		break;
	case 17:
		//����̃g���b�N�̂݃~���[�g�܂��̓\��
		DrawGraph(0, 0, Tutorial_PicHandle17, TRUE);
		break;
	case 18:
		ExplainingDrawGraph(Tutorial_PicHandle17);
		Dtitle("�~���[�g/�\��");
		Dcontent("��������̊y�킪���Ă��钆�A����̊y��̉��������������A�܂��͖炵����\n�Ǝv�����Ƃ�����Ǝv���܂��B����Ȏ��ɕ֗��Ȃ̂��A�~���[�g/�\���@�\�ł��B\n�~���[�g�͓���̊y��̉��������Ƃ��ɁA�\���͓���̊y��̉�������炷\n�Ƃ��Ɏg���܂��B");
		Tmovie
		break;
	case 19:
		//���A���^�C���^�����AMIDI�L�[�{�[�h�őł��Ă���
		DrawGraph(0, 0, Tutorial_PicHandle19, TRUE);
		break;
	case 20:
		ExplainingDrawGraph(Tutorial_PicHandle19);
		Dtitle("���A���^�C���^��");
		Dcontent("�����̉������}�E�X�ň��ł����ނ̂͏����ʓ|�ł��B����ȂƂ���\n�𗧂̂��u���A���^�C���^���v�B�uMIDI�L�[�{�[�h�v�ƌĂ΂�錮�Ղ��g����\n�����ŉ��t���Ȃ�������ǂ��ł����ނ��Ƃ��ł��܂��B�����A���̎��Ɏ኱��\n���Y���̃Y�����o�Ă��܂��̂ŁA�u�N�I���^�C�Y�v�Ƃ��������̏����̃Y����\n�C������@�\���K�v�ł��B");
		//Tmovie
		break;
	case 21:
		////BGM1�̊�����
		DrawGraph(0, 0, Tutorial_PicHandle21, TRUE);
		break;
	case 22:
		Dtitle("�ȏ�ADTM�ɂ��Ẵ`���[�g���A���ł����B\nEnter�������Ɓu�~���[�g/�\���@�\�v�֐i�݂܂��B");
		break;
	case 23://�Ō�𒴂���
		Tutorial_page = 22;
		RootChange(Mix);
		return;
		break;
	case 0://�ŏ����������
		Tutorial_page = 1;
		RootChange(Menu);
		return;
		break;
	}

	//�L�[�{�[�h���f
	if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
		Tutorial_page++;
		Escape_time = 0;
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
		Tutorial_page--;
		Escape_time = 0;
	}
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		Escape_time++;
	}

	//���̑��̕\��
	DrawStringToHandle(300, 670, "'��'�Ŗ߂� '��'�Ői�� Esc2��Ń^�C�g����ʂɖ߂�",Ccontent,LEAD);

	//�G�X�P�[�v�Ɋւ���
	switch (Escape_time){
	case 0:
		break;
	case 1:
		DrawStringToHandle(0, 695, "���ƈ��Esc�L�[�������ƃ^�C�g����ʂɖ߂�܂�", Ccontent, LEAD);
		break;
	case 2:
		RootChange(Menu);
		Escape_time = 0;
		Tutorial_page = 1;
		return;
	}

	//����Đ��Ɋւ���
	if (Keyboard_Get(KEY_INPUT_SPACE)) {
		switch (Tutorial_page){
		case 6:
			system("Movies_T3.mp4");//�C���X�g�D�������g�ꗗ�\����C���X�g�D�������g���N�����āA���h���̉���炷
			break;
		case 8:
			system("Movies_T4.mp4/");//�s�A�m���[����5���ߖڂ̓��ɂSD��z�u���Ė炷
			break;
		case 10:
			system("Movies_T5.mp4");//�䂤�₯���₯�̃m�[�g��ł����݁A�Đ�����
			break;
		case 12:
			system("Movies_T6.mp4");//�䂤�₯���₯�̃I�P���Đ�����
			break;
		case 14:
			system("Movies_T7.mp4");//�䂤�₯���₯�̃I�P���Đ�����
			break;
		case 16:
			system("Movies_T8.mp4");//�䂤�₯���₯�̃I�P���Đ�����
			break;
		case 18:
			system("Movies_T9.mp4");//�䂤�₯���₯�̃X�g�����O�X���~���[�g/�\���ɂ���
			break;
		case 20:
			system(NULL);//���A���^�C���^����BGM1�����t
			break;
		}
	}
}

//�摜�̃o�b�t�@�[
void Tutorial_buffer() {
	 Tutorial_PicHandle01 = LoadGraph("Pics/T1.png");//��{�I�ɂ�M1�Ɠ��������A�A���O����ς���
	 Tutorial_PicHandle03 = LoadGraph("Pics/T2.png");//Studio One�̃z�[�����
	 Tutorial_PicHandle05 = LoadGraph("Pics/T3.png");//�C���X�g�D�������g�ꗗ�\�̃u���E�Y���
	 Tutorial_PicHandle07 = LoadGraph("Pics/T4.png");//�ł����܂ꂽ�s�A�m���[��
	 Tutorial_PicHandle09 = LoadGraph("Pics/T5.png");//�䂤�₯���₯�̃m�[�g��ł����񂾃s�A�m���[��
	 Tutorial_PicHandle11 = LoadGraph("Pics/T6.png");//�s�A�m�g���b�N�ƃV���Z�g���b�N�̕����s�A�m���[��
	 Tutorial_PicHandle13 = LoadGraph("Pics/T7.png");//�����̃g���b�N
	 Tutorial_PicHandle15 = LoadGraph("Pics/T8.png");//�C�R���C�U�[�E�B���h�E�A�~�b�N�X�E�B���h�E
	 Tutorial_PicHandle17 = LoadGraph("Pics/T9.png");//����̃g���b�N�̂݃~���[�g�܂��̓\��
	 Tutorial_PicHandle19 = LoadGraph("Pics/T10.png");//���A���^�C���^�����AMIDI�L�[�{�[�h�őł��Ă���
	 Tutorial_PicHandle21 = LoadGraph("Pics/T11.png");//BGM1�̊�����
	tutorial_PicsBuf_First_time = 1;
}
#include"Menu.h"
#include"Keyboard.h"
#include"Root.h"
#include"DxLib.h"

extern int TITLE;
extern int CONTENT;
extern int LEAD;

int menu_PicsBuf_First_time = 0;
int menu_top_First_time = 0;
int Menu_PicHandle01;

void Menu_main() {
	//�g�b�v�̉��
	if (menu_top_First_time == 0) {
		DrawStringToHandle(500, 0, "�͂��߂�", GetColor(255, 255, 255), TITLE);
		DrawStringToHandle(130, 170, "�{�v���O�����ł́A\n�L�[�{�[�h�ƃw�b�h�t�H�����g�p���܂��B\n���p�ӂ��������B\n�}�E�X�͎g�p���܂���B", GetColor(230, 230, 230), TITLE);
		DrawStringToHandle(480, 670, "�p�ӂł�����Enter", GetColor(220,220,220), LEAD);
		if(Keyboard_Get(KEY_INPUT_RETURN)==1) menu_top_First_time = 1;
		return;
	}
	//�V�[���`�F���W�̃g���K�[
	if (Keyboard_Get(KEY_INPUT_M) == 1) { RootChange(Mix); }
	if (Keyboard_Get(KEY_INPUT_G) == 1) { RootChange(Game); }
	if (Keyboard_Get(KEY_INPUT_T) == 1) { RootChange(Tutorial); }

	//�摜�\��
	if (menu_PicsBuf_First_time == 0) { Menu_buffer(); }
	DrawGraph(0, 0, Menu_PicHandle01, TRUE);

	//�e�L�X�g�\��
	DrawStringToHandle(0, 20, "DTM�ɂ��Ēm�낤", GetColor(255, 255, 255), TITLE);
	DrawStringToHandle(0, 530,"���ӁF�{�v���O�����ł́A�L�[�{�[�h�ƃw�b�h�t�H�����g�p���܂��B\n T->DTM�ɂ��Ẵ`���[�g���A�����J�n(���߂Ă̐l)\n M->�~���[�g / �\��������\n G->���A���^�C���^���Q�[��",GetColor(255,255,255),CONTENT);

}

void Menu_buffer() {
	Menu_PicHandle01 = LoadGraph("Pics/M1.JPG");//StudioOne�ƁAMIDI�L�[�{�[�h���ڑ�����Ă��āA�Đ����̂Ƃ���
	menu_PicsBuf_First_time = 1;
}
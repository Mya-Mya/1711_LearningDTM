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
	//トップの画面
	if (menu_top_First_time == 0) {
		DrawStringToHandle(500, 0, "はじめに", GetColor(255, 255, 255), TITLE);
		DrawStringToHandle(130, 170, "本プログラムでは、\nキーボードとヘッドフォンを使用します。\nご用意ください。\nマウスは使用しません。", GetColor(230, 230, 230), TITLE);
		DrawStringToHandle(480, 670, "用意できたらEnter", GetColor(220,220,220), LEAD);
		if(Keyboard_Get(KEY_INPUT_RETURN)==1) menu_top_First_time = 1;
		return;
	}
	//シーンチェンジのトリガー
	if (Keyboard_Get(KEY_INPUT_M) == 1) { RootChange(Mix); }
	if (Keyboard_Get(KEY_INPUT_G) == 1) { RootChange(Game); }
	if (Keyboard_Get(KEY_INPUT_T) == 1) { RootChange(Tutorial); }

	//画像表示
	if (menu_PicsBuf_First_time == 0) { Menu_buffer(); }
	DrawGraph(0, 0, Menu_PicHandle01, TRUE);

	//テキスト表示
	DrawStringToHandle(0, 20, "DTMについて知ろう", GetColor(255, 255, 255), TITLE);
	DrawStringToHandle(0, 530,"注意：本プログラムでは、キーボードとヘッドフォンを使用します。\n T->DTMについてのチュートリアルを開始(初めての人)\n M->ミュート / ソロを試す\n G->リアルタイム録音ゲーム",GetColor(255,255,255),CONTENT);

}

void Menu_buffer() {
	Menu_PicHandle01 = LoadGraph("Pics/M1.JPG");//StudioOneと、MIDIキーボードが接続されていて、再生中のところ
	menu_PicsBuf_First_time = 1;
}
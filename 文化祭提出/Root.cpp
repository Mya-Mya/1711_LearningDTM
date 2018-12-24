#include"Root.h"
#include"DxLib.h"
#include"Menu.h"
#include"Tutorial.h"
#include"Mix.h"
#include"Game.h"
#include"Keyboard.h"

static RootNow_t RootNow = Menu;

//宣言
int TITLE;
int CONTENT;
int LEAD;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(1280, 720, 16);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	//定義
	TITLE = (CreateFontToHandle("メイリオ", 50, 5, DX_FONTTYPE_ANTIALIASING_EDGE_8X8));
	CONTENT = (CreateFontToHandle("メイリオ", 30, 4, DX_FONTTYPE_ANTIALIASING_EDGE_8X8));
	LEAD = (CreateFontToHandle("メイリオ", 25, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8));

	//メインループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Keyboard_Update();
		switch (RootNow)
		{
		case Menu:
			Menu_main();
			break;
		case Tutorial:
			Tutorial_main();
			break;
		case Mix:
			Mix_mgr();
			break;
		case Game:
			Game_mgr();
			break;
		}
	}
	DxLib_End();
	return 0;
}

void RootChange(RootNow_t RootNext) {
	RootNow = RootNext;
}

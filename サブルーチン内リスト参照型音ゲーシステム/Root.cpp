#include"DxLib.h"
#include"Main.h"
#include"Keyboard.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//SetWindowSizeChangeEnableFlag(TRUE);
	SetGraphMode(1280, 720, 16);
	//SetWindowSize(1280, 720);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//SetWindowPos(GetMainWindowHandle(), NULL, 0, 0, 1280, 720, SWP_FRAMECHANGED || SWP_SHOWWINDOW);
	
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Keyboard_Update();
		Game_mgr();
	}
	DxLib_End();
	return 0;
}
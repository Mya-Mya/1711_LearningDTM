/*
インストゥルメント１：キーボードA
インストゥルメント２：キーボードJ
インストゥルメント０はバッファー時に無視されます
*/


#include"DxLib.h"
#include"Main.h"
#include"Keyboard.h"
#pragma warning(disable:4996)
#include<stdio.h>

static GameNow_t GameNow = selecting;

int Choosing=1;//曲選択
FILE *Score_handle;//譜面データのファイルハンドル

struct Score_List_t {
	int clock;//ノートクロック
	int note;//ノートインストゥルメント
	struct Score_List_t *next;//次のノート
};
struct Score_List_t *FirstList=NULL;//リスト構造の最初
struct Score_List_t *LastList;//リスト構造追加時の作業用ポインタ
struct Score_List_t *NowList;//標的ノートのポインタ
struct Score_List_t *UIList;//UI表示させるための作業用ポインタ

int TMP_clock;//読み出し時、一時的にノートクロック情報を格納する
int TMP_note;//読み出し時、一時的にノートインストゥルメント情報を格納する

int Now_clock = -180;//今の曲進行クロックを格納する
int Good = 0;
int Bad = 0;

struct Score_List_t *ToDeleteList;//消去するための作業用ポインタ
struct Score_List_t *NextDeleteList;//次に消去するための作業用ポインタ

int LastClock;//曲終了時に、その旨の表示時間の保持時間記録用
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
	if(Keyboard_Get(KEY_INPUT_LEFT)==1){//左ボタンが押されていたら
		Choosing--;
		if (Choosing <= 0) { Choosing = 2; };
	}
	if(Keyboard_Get(KEY_INPUT_RIGHT)==1){//右ボタンが押されたら
		Choosing++;
		if (Choosing >= 3) { Choosing = 1; };
	}
	if(Keyboard_Get(KEY_INPUT_RETURN)==1){//Enterが押されたら
		Game_change(buffer);
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "セレクト画面、ただいまの選択曲は%d", Choosing);
}

void Game_buffer() {
	switch (Choosing)//選択曲に応じて読み込むファイルを選択
	{
	case 1:
		Score_handle = fopen("1.csv","r");
		break;
	case 2:
		Score_handle = fopen("2.csv", "r");
		break;
	}
	FirstList = NULL;

	while(fscanf(Score_handle, "%d,%d", &TMP_clock, &TMP_note) != EOF) {//当該譜面ファイルの読み出し行がEOFではない限り
		if((TMP_note)!=0){//ノートインストゥルメントが0以外だったら
			NowList = (Score_List_t*)malloc(sizeof(struct Score_List_t));//マロック、結果をNowListへ
			NowList->clock = TMP_clock, NowList->note = TMP_note, NowList->next = NULL;//読み出したノートデータをこの空間に代入

			if(FirstList==NULL){//もし初めての追加だったら
				FirstList = NowList;//FirstListにこの空間へのアドレスを代入
				LastList = NowList;
			}
			else {
				LastList->next = NowList;//一回前の追加で新規作成された空間内のnextにこの空間へのアドレスを代入
				LastList = NowList;//次回の追加時へのつなぎ
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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "曲進行中。Good=%d Bad=%d Now_clock=%d", Good, Bad, Now_clock);

	if (NowList == NULL) {//もしも曲が終了したら
		DrawFormatString(300, 300, GetColor(255, 255, 255), "曲終了");
		if (Now_clock>LastClock + 240) {//最終のノートクロックから4秒経ったら
			Game_change(result);
			return;
		}
		Now_clock++;
		return;
	}

	Game_UI();//UI表示

	if (Now_clock < 0) {
		DrawFormatString(0, 30, GetColor(255, 255, 255), "Ready?");
	}
	
	if (Now_clock == 0) {
		//音楽再生のコマンド
	}


	if (Now_clock > (NowList->clock) - QUA_CLOCK){
		if(Now_clock < (NowList->clock) + QUA_CLOCK){
			DrawFormatString(0, 100, GetColor(255, 200, 200), "標的ノート範囲内,ノートインストゥルメントは%d",NowList->note);
			if (Keyboard_Get(KEY_INPUT_A) == 1) { if (NowList->note == 1) { Good++, Game_checkin();} };//インストゥルメント１判定
			if (Keyboard_Get(KEY_INPUT_J) == 1) { if (NowList->note == 2) { Good++, Game_checkin();} };//インストゥルメント２判定
		}
		else {//範囲ノート範囲後
			Bad++;
			Game_checkin();
		}
	}
	else {//標的ノート範囲前
		if (Keyboard_Get(KEY_INPUT_A) == 1) { Bad++; };//インストゥルメント１判定
		if (Keyboard_Get(KEY_INPUT_J) == 1) { Bad++; };//インストゥルメント２判定
	}
	Now_clock++;
}

void Game_checkin() {
	LastClock = NowList->clock;
	NowList = NowList->next;//チェックイン
}

void Game_result() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "結果発表 escで選択画面へ");
	DrawFormatString(0, 50, GetColor(200, 200, 200), "Good=%d Bad=%d",Good,Bad);
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		
		//譜面データの解放
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
		if (UIList->note == 2) { UInoteX = 650; }//ノートインストルメントに応じて表示する座標位置を指定

		DrawBox(UInoteX, ToStrike + YperClock*Now_clock - YperClock*UIList->clock, UInoteX + 100, ToStrike + YperClock*Now_clock - YperClock*UIList->clock + 20, GetColor(200, 200, 200), TRUE);
		UIList = UIList->next;
	}
	DrawBox(0, ToStrike, 1280, 720,GetColor(160,160,160),TRUE);
	
}
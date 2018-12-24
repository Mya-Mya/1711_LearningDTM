/*リアルタイム録音ゲー
基本ルール
インストゥルメント０は、アボイドノート・非認識子です。
キックはインストゥルメント１、キーボードＡと対応します。
スネアはインストゥルメント２、キーボードＪと対応します。
両方はインストゥルメント３、キーボードＡＪと対応します。
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
int Now_clock = START_CLOCK;//今の曲進行クロックを格納する
int Good = 0;//標的ノート合格
int Bad = 0;//標的ノート失格
int LastClock = 0;//最後のノートのクロック

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
	Dtitle("リアルタイム録音ゲーム");
	DrawStringToHandle(50, 100, "ここでは、DAWのリアルタイム録音の機能を実感してもらうために、BGMの進行と\nともにドラム(キック・スネア)を打ち込んでもらいます。Aでキックを、Jでスネア\nを打ち込みます。少しのズレはクオンタイズに修正してもらえますが、あまりにも\nズレすぎていると失点となります。「ミュート/ソロ機能」にてドラムのリズムを\n確認することをおすすめします。BGMを選びEnterを押して開始します。", Ccontent, CONTENT);

	//キーボード操作
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
	
	//その他の表示
	DrawStringToHandle(200, 690, "←→で選曲 Enterで再生 Spaceでミュート/ソロ機能へ Escでタイトル画面へ", Ccontent, LEAD);
	DrawFormatStringToHandle(470, 450, GetColor(255, 100, 100), CONTENT, "BGM%dを選択中です", game_choosing);
}

int Game_SoundHandles[7] = { 0 };//それぞれのパートのサウンドハンドル
int KickSoundHandle, SnareSoundHandle, BothSoundHandle;//インストゥルメントのサウンドを再生する
FILE *Score_handle;//譜面データのファイルハンドル

struct Score_List_t {//各ノートのデータ
	int clock;//各ノートのクロック
	int note;//各ノートのインストゥルメント
	struct Score_List_t *next;//次のノート
};
struct Score_List_t *FirstList = NULL;//リスト構造の最初
struct Score_List_t *LastList;//リスト構造追加時の作業用ポインタ
struct Score_List_t *NowList;//標的ノートのポインタ
struct Score_List_t *UIList;//UI表示させるための作業用ポインタ

int READ_clock;//読み出し時、一時的にノートクロック情報を格納する
int READ_note;//読み出し時、一時的にノートインストゥルメント情報を格納する

void Game_buffer() {
	InitSoundMem();//メモリ上の全てのサウンドを消去
	//音楽ファイルと譜面データのファイルを指定
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

	//譜面データファイルから読み出し各ノートデータのリストを構成する
	while(fscanf(Score_handle,"%d,%d",&READ_clock,&READ_note)!=EOF){//ノートを1つずつ読み出す
		if (READ_note != AVOID_NOTE) {//今のインストゥルメントが非認識子でないかぎり
			NowList = (Score_List_t*)malloc(sizeof(struct Score_List_t));//動的メモリ確保
			NowList->clock = READ_clock, NowList->note = READ_note, NowList->next = NULL;//新規空間上にノート情報をコピー
			if (FirstList == NULL) {//もし初めての追加だったら
				FirstList = NowList;//FirstListにこの空間へのアドレスを代入
				LastList = NowList;
			}
			else {
				LastList->next = NowList;//一回前の追加で新規作成された空間内のnextにこの空間へのアドレスを代入
				LastList = NowList;//次回の追加時へのつなぎ
			}
		}
	}

	//ゲーム進行時の変数の初期化
	NowList = FirstList;
	UIList = FirstList;
	Game_change(game_play);
}

#define Game_PLAY_MESSAGE(x,y,in) DrawStringToHandle(x,y,in,Ccontent,CONTENT)

//譜面データのチェックインを行う
void Game_checkin() {
	LastClock = NowList->clock;
	NowList = NowList->next;
}

//得点に関するマクロ・制御
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

//譜面を表示する
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
	//得点UI通知
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


//インストゥルメントのサウンドを再生する
void Game_InstrumentsSound() {
	if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) == 1) PlaySoundMem(BothSoundHandle, DX_PLAYTYPE_BACK, TRUE);
	if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) != 1) PlaySoundMem(KickSoundHandle, DX_PLAYTYPE_BACK, TRUE);
	if (Keyboard_Get(KEY_INPUT_A) != 1 && Keyboard_Get(KEY_INPUT_J) == 1) PlaySoundMem(SnareSoundHandle, DX_PLAYTYPE_BACK, TRUE);
}


//中止の際のお知らせ用変数
#define DefaultStopClock 60
int StopClock = DefaultStopClock;

//進行メインルーチン
void Game_play() {
	DrawFormatStringToHandle(0, 0, Ccontent, CONTENT, "BGM%dを再生中　Escで中止", game_choosing);

	Game_InstrumentsSound();//インストゥルメントのサウンドを再生する
	Game_UI();

	//曲の末端があったら
	if(NowList==NULL){
		Game_PLAY_MESSAGE(550, 350, "終了");
		if (Now_clock>LastClock + 240) {//最終のノートクロックから4秒経ったら
			Game_change(game_result);
			return;
		}
		Now_clock++;
		return;
	}

	//待機中のメッセージ
	if (Now_clock < 0) {
		Game_PLAY_MESSAGE(550,350, "Ready ?");
	}

	//音楽ファイル再生開始
	if (Now_clock == 0) {
		for (int i = 0; i < 7; i++) {
			if (i == 1) { i = 2; }//皮ドラムの消音
			PlaySoundMem(Game_SoundHandles[i], DX_PLAYTYPE_BACK, TRUE);
			ChangeVolumeSoundMem(220, Game_SoundHandles[i]);
		}
	}

	//判定
	if (Now_clock >(NowList->clock) - QUA_CLOCK) {
		if (Now_clock < (NowList->clock) + QUA_CLOCK) {
			if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) == 1) { if (NowList->note == BOTH) { PointChange(GOOD), Game_checkin(); } }//インストゥルメント３判定
			if (Keyboard_Get(KEY_INPUT_A) == 1 && Keyboard_Get(KEY_INPUT_J) != 1) { if (NowList->note == KICK) { PointChange(GOOD), Game_checkin(); } };//インストゥルメント１判定
			if (Keyboard_Get(KEY_INPUT_A) != 1 && Keyboard_Get(KEY_INPUT_J) == 1) { if (NowList->note == SNARE) { PointChange(GOOD), Game_checkin(); } };//インストゥルメント２判定
		}
		else {//範囲ノート範囲後
			PointChange(BAD);
			Game_checkin();
		}
	}
	else {//標的ノート範囲前
		if (Keyboard_Get(KEY_INPUT_A) == 1) { PointChange(BAD); };//インストゥルメント１判定
		if (Keyboard_Get(KEY_INPUT_J) == 1) { PointChange(BAD); };//インストゥルメント２判定
	}

	//中止
	if (StopClock != DefaultStopClock) {
		Game_PLAY_MESSAGE(550, 350, "中止します");
		StopClock++;
		if (StopClock == DefaultStopClock-1) StopClock = DefaultStopClock, Game_change(game_result);
	}
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		StopClock=0;//中止待機処理のトリガーを作る
	}

	//ルール説明
	if (-70<Now_clock && Now_clock < 150) {
		DrawLine(350, ToStrike-2, 960, ToStrike-2, GetColor(255, 255, 100));
		Game_PLAY_MESSAGE(240, 610, "この境界線に緑色の音符が落ちてきた瞬間にAまたはJを押します。");
	}

	//曲進行
	Now_clock++;
}

void Game_change(GameNow_t GameNext) {
	GameNow = GameNext;
}


//結果の表示およびリセット
struct Score_List_t *ToDeleteList;
struct Score_List_t *NextDeleteList;
void Game_result() {
	for (int i = 0; i < 7; i++) {
		StopSoundMem(Game_SoundHandles[i]);
	}
	DrawFormatStringToHandle(0, 150, Ccontent, CONTENT, "スコアはGood = %d  Bad = %d でした。\nプレイして頂きありがとうございました。 Escで選択画面へ戻ります。", Good, Bad);
	void Game_result_comment();

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		//譜面データの解放
		ToDeleteList = FirstList;
		NextDeleteList = FirstList;
		while (ToDeleteList != NULL) {
			NextDeleteList = ToDeleteList->next;
			free(ToDeleteList);
			ToDeleteList = NextDeleteList;
		}

		FirstList = NULL;
		Now_clock = START_CLOCK;//ゲーム進行クロックをリセット
		Good = 0, Bad = 0;
		Game_change(game_selecting);
	}
}

void Game_result_comment() {
	char Message[128];
	DrawFormatStringToHandle(30, 400, GetColor(200, 200, 200), CONTENT, "%s", Message);
}
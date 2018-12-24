#include<dshow.h>
#include"Root.h"
#include"Tutorial.h"
#include"Keyboard.h"
#include"DxLib.h"
#include <stdlib.h>
#include<Windows.h>

//進行用変数
int Tutorial_page = 1;
int Escape_time = 0;

//画像ハンドル
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

#define Tmovie DrawStringToHandle(0,530,"Spaceで動画を見る",GetColor(255,150,150),CONTENT);

//説明文章の裏に挿入する用の透過画像を投下
void ExplainingDrawGraph(int Handle) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
	DrawGraph(0, 0, Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Tutorial_main() {
	
	if(tutorial_PicsBuf_First_time==0){//初めてのアクセスだったら
		Tutorial_buffer();
		return;
	}
	//メインコンテンツの表示
	switch(Tutorial_page) {
	case 1:
		//基本的にはM1と等しいが、アングルを変える
		DrawGraph(0, 0, Tutorial_PicHandle01,TRUE);
		Dtitle("チュートリアル");
		break; 
	case 2:
		ExplainingDrawGraph(Tutorial_PicHandle01);
		Dtitle("DTMって何？");
		Dcontent("PCを使って音楽制作をすることをDTM(DeskTop Music・デスクトップミュージック)\nと呼びます。アーティストのプロデューサーやサウンドクリエイター等の\nプロも行っていて、簡単に作曲や編曲ができます。");
		break;
	case 3:
		//Studio Oneのホーム画面
		DrawGraph(0, 0, Tutorial_PicHandle03, TRUE);
		break;
	case 4:
		ExplainingDrawGraph(Tutorial_PicHandle03);
		Dtitle("DTM専用ソフトウェア「DAW」");
		Dcontent("音楽制作をするソフトウェアを一般的に「DAW」といいます。無料のものから、\n有名なアイドルグループのプロデューサーも使っているような高価なものまで\nたくさんあります。この画像は、私が使っているPronouns社の「Studio One」\nというDAWの画面です。次のページからは、Studio Oneの実際の画面と共に、\nDAWができること、DTMでできることを説明します。");
		break;
	case 5:
		//インストゥルメント一覧表のブラウズ画面
		DrawGraph(0, 0, Tutorial_PicHandle05, TRUE);
		break;
	case 6:
		ExplainingDrawGraph(Tutorial_PicHandle05);
		Dtitle("色々な楽器を試す ");
		Dcontent("DAW内には「ソフトウェア音源」という、実際のシンセサイザーやピアノ、ギター、\nドラムなどの様々な楽器の音をシミュレートするプログラムが組み込まれています。\nStudio Oneではソフトウェア音源のプログラムを「インストゥルメント」と\n呼ばれているので、以後そう呼ぶことにします。ここでは、シンセサイザーの\nインストゥルメントを起動し、<ド>の音を鳴らしてみました。");
		Tmovie
		break;
	case 7:
		//打ち込まれたピアノロール
		DrawGraph(0, 0, Tutorial_PicHandle07, TRUE);
		break;
	case 8:
		ExplainingDrawGraph(Tutorial_PicHandle07);
		Dtitle("演奏してもらう");
		Dcontent("起動したインストゥルメントに、自動演奏してもらいます。「ピアノロール」\nと呼ばれるこの表は、縦軸が音の高さで、横軸が時間を示しています。ここでは、\n5小節目の頭に<レ>の4分音符を配置しました。このように、音符を配置することを\n「打ち込む」といいます。");
		Tmovie
		break;
	case 9:
		//ゆうやけこやけのノートを打ち込んだピアノロール
		DrawGraph(0, 0, Tutorial_PicHandle09, TRUE);
		break;
	case 10:
		ExplainingDrawGraph(Tutorial_PicHandle09);
		Dtitle("演奏してもらう(2)");
		Dcontent("「ゆうやけこやけ」という童謡楽曲のメロディを打ち込み、再生ボタンを押して\n演奏してもらいました。シンセサイザーの音で「ゆうやけこやけ」が流れました。");
		Tmovie
		break;
	case 11:
		//ピアノトラックとシンセトラックの複合ピアノロール
		DrawGraph(0, 0, Tutorial_PicHandle11, TRUE);
		break;
	case 12:
		ExplainingDrawGraph(Tutorial_PicHandle11);
		Dtitle("伴奏を付け足す");
		Dcontent("次にピアノの音で伴奏を付け足してもらおうと思います。追加でピアノの\nインストゥルメントを起動して、伴奏を打ち込みました。赤い音符がメロディ、\n黒い音符が伴奏です。");
		Tmovie
		break;
	case 13:
		//多数のトラック
		DrawGraph(0, 0, Tutorial_PicHandle13, TRUE);
		break;
	case 14:
		ExplainingDrawGraph(Tutorial_PicHandle13);
		Dtitle("さらに色々な楽器を付け足す");
		Dcontent("さらに楽器を付け足して豪華にしてみました。でも、あまり綺麗に聞こえません。\nそれぞれの楽器が調和していないからです。音を綺麗に聞こえさせるために\n加工が必要なのです。");
		Tmovie
		break;
	case 15:
		//イコライザーウィンドウ、ミックスウィンドウ
		DrawGraph(0, 0, Tutorial_PicHandle15, TRUE);
		break;
	case 16:
		ExplainingDrawGraph(Tutorial_PicHandle15);
		Dtitle("ミックス/マスタリング");
		Dcontent("それぞれの音を加工することを「ミックス」または「マスタリング」といいます。\nそれぞれの楽器の音を整えて全体的に綺麗に聞こえるようにします。\n多彩な楽器が集まって美しいハーモニーとなりました。");
		Tmovie
		break;
	case 17:
		//特定のトラックのみミュートまたはソロ
		DrawGraph(0, 0, Tutorial_PicHandle17, TRUE);
		break;
	case 18:
		ExplainingDrawGraph(Tutorial_PicHandle17);
		Dtitle("ミュート/ソロ");
		Dcontent("たくさんの楽器が鳴っている中、特定の楽器の音だけ消したい、または鳴らしたい\nと思うこともあると思います。そんな時に便利なのが、ミュート/ソロ機能です。\nミュートは特定の楽器の音を消すときに、ソロは特定の楽器の音だけを鳴らす\nときに使います。");
		Tmovie
		break;
	case 19:
		//リアルタイム録音中、MIDIキーボードで打っている
		DrawGraph(0, 0, Tutorial_PicHandle19, TRUE);
		break;
	case 20:
		ExplainingDrawGraph(Tutorial_PicHandle19);
		Dtitle("リアルタイム録音");
		Dcontent("多数の音符をマウスで一つ一つ打ち込むのは少し面倒です。そんなときに\n役立つのが「リアルタイム録音」。「MIDIキーボード」と呼ばれる鍵盤を使って\n自分で演奏しながら効率良く打ち込むことができます。ただ、この時に若干の\nリズムのズレが出てしまうので、「クオンタイズ」という音符の少しのズレを\n修正する機能が必要です。");
		//Tmovie
		break;
	case 21:
		////BGM1の完成版
		DrawGraph(0, 0, Tutorial_PicHandle21, TRUE);
		break;
	case 22:
		Dtitle("以上、DTMについてのチュートリアルでした。\nEnterを押すと「ミュート/ソロ機能」へ進みます。");
		break;
	case 23://最後を超えた
		Tutorial_page = 22;
		RootChange(Mix);
		return;
		break;
	case 0://最初を下回った
		Tutorial_page = 1;
		RootChange(Menu);
		return;
		break;
	}

	//キーボード判断
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

	//その他の表示
	DrawStringToHandle(300, 670, "'←'で戻る '→'で進む Esc2回でタイトル画面に戻る",Ccontent,LEAD);

	//エスケープに関して
	switch (Escape_time){
	case 0:
		break;
	case 1:
		DrawStringToHandle(0, 695, "あと一回Escキーを押すとタイトル画面に戻ります", Ccontent, LEAD);
		break;
	case 2:
		RootChange(Menu);
		Escape_time = 0;
		Tutorial_page = 1;
		return;
	}

	//動画再生に関して
	if (Keyboard_Get(KEY_INPUT_SPACE)) {
		switch (Tutorial_page){
		case 6:
			system("Movies_T3.mp4");//インストゥルメント一覧表からインストゥルメントを起動して、＜ド＞の音を鳴らす
			break;
		case 8:
			system("Movies_T4.mp4/");//ピアノロールの5小節目の頭に４Dを配置して鳴らす
			break;
		case 10:
			system("Movies_T5.mp4");//ゆうやけこやけのノートを打ち込み、再生する
			break;
		case 12:
			system("Movies_T6.mp4");//ゆうやけこやけのオケを再生する
			break;
		case 14:
			system("Movies_T7.mp4");//ゆうやけこやけのオケを再生する
			break;
		case 16:
			system("Movies_T8.mp4");//ゆうやけこやけのオケを再生する
			break;
		case 18:
			system("Movies_T9.mp4");//ゆうやけこやけのストリングスをミュート/ソロにする
			break;
		case 20:
			system(NULL);//リアルタイム録音でBGM1を演奏
			break;
		}
	}
}

//画像のバッファー
void Tutorial_buffer() {
	 Tutorial_PicHandle01 = LoadGraph("Pics/T1.png");//基本的にはM1と等しいが、アングルを変える
	 Tutorial_PicHandle03 = LoadGraph("Pics/T2.png");//Studio Oneのホーム画面
	 Tutorial_PicHandle05 = LoadGraph("Pics/T3.png");//インストゥルメント一覧表のブラウズ画面
	 Tutorial_PicHandle07 = LoadGraph("Pics/T4.png");//打ち込まれたピアノロール
	 Tutorial_PicHandle09 = LoadGraph("Pics/T5.png");//ゆうやけこやけのノートを打ち込んだピアノロール
	 Tutorial_PicHandle11 = LoadGraph("Pics/T6.png");//ピアノトラックとシンセトラックの複合ピアノロール
	 Tutorial_PicHandle13 = LoadGraph("Pics/T7.png");//多数のトラック
	 Tutorial_PicHandle15 = LoadGraph("Pics/T8.png");//イコライザーウィンドウ、ミックスウィンドウ
	 Tutorial_PicHandle17 = LoadGraph("Pics/T9.png");//特定のトラックのみミュートまたはソロ
	 Tutorial_PicHandle19 = LoadGraph("Pics/T10.png");//リアルタイム録音中、MIDIキーボードで打っている
	 Tutorial_PicHandle21 = LoadGraph("Pics/T11.png");//BGM1の完成版
	tutorial_PicsBuf_First_time = 1;
}
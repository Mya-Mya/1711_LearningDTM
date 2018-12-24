#pragma once

typedef enum {
	game_selecting,
	game_buffer,
	game_play,
	game_result,
}GameNow_t;

//#ifdef GameDef
//#define GameDef

void Game_mgr();
void Game_select();
void Game_buffer();
void Game_change(GameNow_t GameNext);
void Game_play();
void Game_result();
void Game_result_comment();

//#endif // GameDef
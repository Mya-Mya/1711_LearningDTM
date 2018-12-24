#pragma once
typedef enum {
	selecting,
	buffer,
	play,
	result,
}GameNow_t;

void Game_mgr();
void Game_buffer();
void Game_select();
void Game_change(GameNow_t GameNext);
void Game_play();
void Game_result();
void Game_checkin();
void Game_UI();
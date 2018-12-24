#pragma once

typedef enum {
	intro,
	buffer,
	play,
}MixNow_t;

#ifndef MixDef
#define MixDef
void Mix_mgr();
void Mix_change(MixNow_t MixNext);
void Mix_intro();
void Mix_buffer();
void Mix_play();
#endif // !MixDef

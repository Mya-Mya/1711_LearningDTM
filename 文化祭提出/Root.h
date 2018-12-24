#pragma once

#ifndef RootDef
#define RootDef

typedef enum {
	Menu,
	Tutorial,
	Mix,
	Game,
}RootNow_t;

void RootChange(RootNow_t RootNext);

#endif // !RootDef

#pragma once

#include<Windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27

#define MAP_X 3
#define MAP_Y 2
#define MAP_W 30
#define MAP_H 20

int x[1000], y[1000];
int itemX, itemY;
int snakeLength;
int speed;
int score;
int best_score = 0;
int last_score = 0;
int dir;
int input;

void gotoxy(int x, int y, char* s)
{
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}

/// <summary>
/// 맵 테두리 부분
/// </summary>
/// <param name=""></param>
void DrawMap(void) {

	for (int i = 0; i < MAP_W; i++)
	{
		gotoxy(MAP_X + i, MAP_Y, "■");
	}

	for (int i = MAP_Y + 1; i < MAP_Y + MAP_H - 1; i++)
	{
		gotoxy(MAP_X, i, "■");
		gotoxy(MAP_X + MAP_W - 1, i, "■");
	}

	for (int i = 0; i < MAP_W; i++)
	{
		gotoxy(MAP_X + i, MAP_Y + MAP_H - 1, "■");
	}
}

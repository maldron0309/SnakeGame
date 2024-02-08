

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include"game.h"


void Title(void);
void Reset(void);
void GameOver(void);

void DrawMap(void);
void Move(int dir);
void Item(void);

int main() {
	Title();

	while (1) 
	{
		if (_kbhit()) do { input = _getch(); } while (input == 224);
		Sleep(speed);

		switch (input) {
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((dir == LEFT && input != RIGHT) || (dir == RIGHT && input != LEFT) || (dir == UP && input != DOWN) ||
				(dir == DOWN && input != UP))// 회전 이동 방지
				dir = input;
			input = 0;
			break;
		case ESC: // 종료 
			exit(0);
		}
		Move(dir);
	}
}


void Title(void) {
	int i, j;

	while (_kbhit()) _getch();

	DrawMap();
	for (i = MAP_Y + 1; i < MAP_Y + MAP_H - 1; i++)
	{
		for (j = MAP_X + 1; j < MAP_X + MAP_W - 1; j++)
		{
			gotoxy(j, i, "  ");
		}
	}

	gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 5, "+--------------------------+");
	gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 6, "|        S N A K E         |");
	gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 7, "+--------------------------+");

	gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 9, " < PRESS ANY KEY TO START > ");

	gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 11, "   ◇ ←,→,↑,↓ : Move    ");
	gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 13, "   ◇ ESC : Quit              ");


	while (1) {
		if (_kbhit()) {
			input = _getch();
			if (input == ESC) exit(0); // ESC키면 종료 
			else break;
		}
		gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 9, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 9, "                            ");
		Sleep(400);

	}
	Reset();
}

/// <summary>
/// 초기화
/// </summary>
/// <param name=""></param>
void Reset(void) {

	system("cls");
	DrawMap();
	while (_kbhit()) _getch();

	dir = LEFT;
	speed = 100;
	snakeLength = 5;
	score = 0;

	for (int i = 0; i < snakeLength; i++)
	{
		x[i] = MAP_W / 2 + i;
		y[i] = MAP_H / 2;
		gotoxy(MAP_X + x[i], MAP_Y + y[i], "@");
	}

	gotoxy(MAP_X + x[0], MAP_Y + y[0], "☆");
	Item();
}


void Move(int dir) {

	int i;

	// item이랑 충돌했을 경우 
	if (x[0] == itemX && y[0] == itemY)
	{
		score += 10; // 점수 증가 
		Item(); // 새로운 item 추가
		snakeLength++; // 길이 증가 
		x[snakeLength - 1] = x[snakeLength - 2];
		y[snakeLength - 1] = y[snakeLength - 2];
	}

	// 벽과 충돌했을 경우 
	if (x[0] == 0 || x[0] == MAP_W - 1 || y[0] == 0 || y[0] == MAP_H - 1)
	{
		GameOver();
		return;

	}

	// 자기몸과 충돌했는지 검사
	for (i = 1; i < snakeLength; i++)
	{
		if (x[0] == x[i] && y[0] == y[i]) {
			GameOver();
			return;
		}
	}

	gotoxy(MAP_X + x[snakeLength - 1], MAP_Y + y[snakeLength - 1], "  ");
	for (i = snakeLength - 1; i > 0; i--) 
	{
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	gotoxy(MAP_X + x[0], MAP_Y + y[0], "@");
	if (dir == LEFT) --x[0];
	if (dir == RIGHT) ++x[0];
	if (dir == UP) --y[0];
	if (dir == DOWN) ++y[0];
	gotoxy(MAP_X + x[i], MAP_Y + y[i], "☆");
}

/// <summary>
/// 게임 종료
/// </summary>
/// <param name=""></param>
void GameOver(void) {
	gotoxy(MAP_X + (MAP_W / 2) - 6, MAP_Y + 5, "+----------------------+");
	gotoxy(MAP_X + (MAP_W / 2) - 6, MAP_Y + 6, "|      GAME OVER..     |");
	gotoxy(MAP_X + (MAP_W / 2) - 6, MAP_Y + 7, "+----------------------+");
	gotoxy(MAP_X + (MAP_W / 2) - 6, MAP_Y + 8, " YOUR SCORE : ");
	printf("%d", last_score = score);

	gotoxy(MAP_X + (MAP_W / 2) - 7, MAP_Y + 12, " Press any keys to restart.. ");

	if (score > best_score) {
		best_score = score;
		gotoxy(MAP_X + (MAP_W / 2) - 4, MAP_Y + 10, "☆ BEST SCORE ☆");
	}
	Sleep(500);
	while (_kbhit()) _getch();
	input = _getch();
	Title();
}

void Item(void) {

	int itemCrush = 0;
	int r = 0;
	gotoxy(MAP_X, MAP_Y + MAP_H, " YOUR SCORE: ");
	printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);

	while (1)
	{
		itemCrush = 0;
		srand((unsigned)time(NULL) + r);
		itemX = (rand() % (MAP_W - 2)) + 1;
		itemY = (rand() % (MAP_H - 2)) + 1;

		// item이 몸통과 겹치는지 확인
		for (int i = 0; i < snakeLength; i++)
		{
			if (itemX == x[i] && itemY == y[i])
			{
				itemCrush = 1;
				r++;
				break;
			}
		}

		if (itemCrush == 1)
		{
			continue;
		}

		gotoxy(MAP_X + itemX, MAP_Y + itemY, "♪");
		speed -= 3; //속도 증가 
		break;

	}
}




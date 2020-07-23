#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define SCREEN_WIDTH 13
#define SCREEN_HEIGHT 13
#define POINT 10
#define SHOT_MAX 5

typedef struct {
	int x, y;
	bool state;

}SHOT;
SHOT shots[SHOT_MAX];
enum {
	OFF,
	ON,
};
int point = 0;
enum {
	CELL_TYPE_NONE,
	CELL_TYPE_BLOCK,
	CELL_TYPE_POINT,
	CELL_TYPE_SHOT,
	CELL_TYPE_MAX
};
enum {
	DIRECTION_NORTH,
	DIRECTION_WEST,
	DIRECTION_SOUTH,
	DIRECTION_EAST,
	DIRECTION_MAX
};
enum {
MAN,
Alien1,
Alien2,
Alien3,
Alien_MAX
};
int directions[][2] = {
	{0,-1},//DIRECTION_NORTH,
	{-1,0},//DIRECTION_WEST,
	{0,1},//DIRECTION_SOUTH,
	{1,0}//DIRECTION_EAST,
};
char cellAA[][2 + 1] = {
	"　",//CELL_TYPE_NONE,
	"■",//CELL_TYPE_BLOCK,
	"・",//CELL_TYPE_POINT
	"○"
	};
int cells[SCREEN_HEIGHT][SCREEN_WIDTH];
typedef struct {
	int x, y;
	int directions;
}Alien;

Alien aliens[Alien_MAX];



int getMonster(int _x, int _y) {
	for (int i = 0; i < Alien_MAX; i++)
		if ((aliens[i].x == _x) && (aliens[i].y == _y))
			return i;
	return -1;
}
void setFreePosition(int* pX, int* pY) { //初期エイリアン配置
	while (1) {
		int x = rand() % SCREEN_WIDTH;
		int y = rand() % SCREEN_HEIGHT;
		switch (cells[y][x]) {
		case CELL_TYPE_BLOCK:  //壁ならやり直し
			break;
		default:
		{
			int monster = getMonster(x, y);
			if (monster < MAN) {  //パックマンでないならセット
				*pX = x;
				*pY = y;
				return;
			}
		}
		}
	}

}
int getShot(int _x, int _y) {
	for (int i = 0; i < SHOT_MAX; i++)
		if ((shots[i].x == _x) && (shots[i].y == _y))
			return i;
	return -1;

}
int getFreeShot() {
	for (int i = 0; i < SHOT_MAX; i++) {
		if (shots[i].state == 0)
			return i;
		return -1;
	}
}
void init() {
	srand((unsigned int)time(NULL));
	

	for (int y = 0; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT - 1)
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			cells[y][x] = CELL_TYPE_BLOCK;
		}
	for (int y = 0; y < SCREEN_HEIGHT; y++)
		for (int x = 0; x < SCREEN_WIDTH; x += SCREEN_WIDTH - 1) {
			cells[y][x] = CELL_TYPE_BLOCK;
		}
	for (int y = 0; y < SCREEN_HEIGHT; y++)
		for (int x = 1; x < SCREEN_WIDTH - 1; x++) {
			if ((x % 2 == 0) && (y % 2 == 0))
				cells[y][x] = CELL_TYPE_BLOCK;
		}
	for (int y = 0; y < SCREEN_HEIGHT; y++)
		for (int x = 1; x < SCREEN_WIDTH - 1; x++) {
			if (!cells[y][x] == CELL_TYPE_BLOCK)
				cells[y][x] = CELL_TYPE_POINT;
		}
	//cells[SCREEN_HEIGHT / 2][SCREEN_WIDTH / 2] = CELL_TYPE_NONE;

	aliens[MAN].x = SCREEN_HEIGHT / 2 + 1;
	aliens[MAN].y = SCREEN_HEIGHT / 2 + 1;

	for (int i = 1; i < Alien_MAX; i++)
		setFreePosition(&aliens[i].x, &aliens[i].y);
}
void display() {
	system("cls");
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			int shot_M = getShot(x, y);
			int alien = getMonster(x, y);
			if (shot_M > 0)
				printf("→");
			if (alien < 0)
				printf(cellAA[cells[y][x]]);
			else if (alien > MAN)
				printf("敵");

			else
				printf("＠");
		}
		printf("\n");
	}
	printf("point  %d", point);

}
void gameOver() {
	aliens[MAN].x = -1;
	aliens[MAN].y = -1;
	display();
	printf("\n GAME OVER");
	_getch();
	exit(0);
}
void alienMove() {
	for (int i =MAN+ 1; i < Alien_MAX; i++) {  //Alienの移動
		int x = aliens[i].x + directions[aliens[i].directions][0];
		int y = aliens[i].y + directions[aliens[i].directions][1];
	
		int alien = getMonster(x, y);
		if (alien == MAN) {
			aliens[i].x = x;
			aliens[i].y = y;
			gameOver();
		}
		else if ((cells[y][x] == CELL_TYPE_BLOCK)//壁だったら変更
			|| (alien > MAN)) {

			aliens[i].directions = rand() % DIRECTION_MAX;
		}
		else {
			aliens[i].x = x;
			aliens[i].y = y;
		}
	}
	
}
int main() {
	init();
	time_t t = time(NULL);


	while (1) {
		display();
		if (time(NULL) > t) {
			t = time(NULL);
			display();
		}
		
		int x = aliens[0].x;//ｘ座標
		int y = aliens[0].y;

		switch (_getch()) {
		case 'w':y--; break;
		case 's':y++; break;
		case 'a':x--; break;
		case 'd':x++; break;
		case 'm':
			int shot = getFreeShot();
			if (shot >= 0) {
				shots[shot].x = aliens[0].x;
				shots[shot].y = aliens[0].y;
				shots[shot].state = 1;
				//printf("→");
			}break;
			display();
		}
		switch (cells[y][x]) {
		case CELL_TYPE_BLOCK:
			break;
		case CELL_TYPE_POINT:
			cells[y][x] = CELL_TYPE_NONE;
			point += POINT;
		default:
			aliens[0].x = x;
			aliens[0].y = y;
			break;
		}
		alienMove();

}
	
}

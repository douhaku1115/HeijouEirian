#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define SCREEN_WIDTH 13
#define SCREEN_HEIGHT 13
#define Alien_MAX 4
enum {
	CELL_TYPE_NONE,
	CELL_TYPE_BLOCK,
	CELL_TYPE_POINT,
	CELL_TYPE_MAX
};
char cellAA[][2 + 1] = {
	"@",//CELL_TYPE_NONE,
	"¡",//CELL_TYPE_BLOCK,
	"E"//CELL_TYPE_POINT
};
int cells[SCREEN_HEIGHT][SCREEN_WIDTH];
typedef struct {
	int x, y;
}Alien;

Alien aliens[Alien_MAX];

int getMonster(int _x, int _y) {
	for (int i = 0; i < Alien_MAX; i++)
		if ((aliens[i].x == _x) && (aliens[i].y == _y))
			return i;
	return -1;
}
void setFreePosition(int* pX, int* pY) {
	while (1) {
		int x = rand() % SCREEN_WIDTH;
		int y = rand() % SCREEN_HEIGHT;
		switch (cells[y][x]) {
		case CELL_TYPE_BLOCK:
			break;
			default:
		{
			int monster = getMonster(x, y);
			if (monster < 0) {
				*pX = x;
				*pY = y;
				return;
			}
		}
		}
	}

}
int main() {

	for (int y=0 ;y<SCREEN_HEIGHT;y+=SCREEN_HEIGHT-1)
		for (int x=0; x < SCREEN_WIDTH; x++) {
			cells[y][x] = CELL_TYPE_BLOCK;
		}
	for (int y = 0; y < SCREEN_HEIGHT; y++)
		for (int x = 0; x < SCREEN_WIDTH; x+=SCREEN_WIDTH-1) {
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

	aliens[0].x = SCREEN_HEIGHT / 2+1;
	aliens[0].y = SCREEN_HEIGHT / 2+1;

	for (int i = 1; i < Alien_MAX; i++)
		setFreePosition(&aliens[i].x, &aliens[i].y);

	
	while (1) {
		system("cls");
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				int alien = getMonster(x, y);
				if (alien < 0)
					printf(cellAA[cells[y][x]]);
				else if (alien > 0)
					printf("“G");
				else
					printf("—");
			}
			printf("\n");
		}


		int x = aliens[0].x;//ｘ座標
		int y = aliens[0].y;　//ｙ座標

		switch (_getch()) {
		case 'w':y--; break;
		case 's':y++; break;
		case 'a':x--; break;
		case 'd':x++; break;
		}
		switch (cells[y][x]) {
		case CELL_TYPE_BLOCK:
			break;
		default:
			aliens[0].x = x;
			aliens[0].y = y;
			break;
		}
	}

	
}

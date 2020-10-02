# include "iGraphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
using namespace std;

int score = 0, flag = 0;
int game_is_over = 0, game_is_started = 0;
int i, j;

int grid[4][4] = { 0 };
int dx, dy;
char buffer[33];

int digit(int n)
{
	int ret = 0;
	while (n){
		n /= 10;
		ret++;
	}
	return ret;
}

int reverse(int n)
{
	int ret = 0;
	while (n){
		ret = ret * 10 + n % 10;
		n /= 10;
	}
	return ret;
}

void printScore()
{
	iSetcolor(0, 127, 0);
	iText(700, 200, "Score : ", GLUT_BITMAP_TIMES_ROMAN_24);

	/*itoa(score, buffer, 10);
	iSetcolor(0, 127, 0);
	iText(750, 200, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	buffer[33] = '\0';*/

	if (!score){
		iSetcolor(0, 127, 0);
		iText(770, 200, "0", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else{

		int rest = reverse(score);
		int dig = digit(score);
		char ch;
		int i = 770;
		int ret = rest;
		while (rest){

			ch = rest % 10 + 48;
			rest /= 10;
			iSetcolor(0, 127, 0);
			iText(i, 200, &ch, GLUT_BITMAP_TIMES_ROMAN_24);
			i += 10;
		}

		if (digit(ret) != dig){
			int diff = dig - digit(ret);
			while (diff--){
				iSetcolor(0, 127, 0);
				iText(i, 200, "0", GLUT_BITMAP_TIMES_ROMAN_24);
				i += 10;
			}
		}
	}
}

void bestScore()
{
	//freopen("best_score.txt", "r", stdin);
	ifstream fin("best_score");
	int best_score;
	//scanf("%d", &best_score);
	fin >> best_score;
	fclose(stdout);
	if (score > best_score){
		//freopen("best_score.txt", "w", stdout);
		ofstream fout("best_score");
		best_score = score;
		//printf("%d", best_score);
		fout << best_score;
		fclose(stdout);
	}

	iSetcolor(0, 127, 0);
	iText(700, 300, "Best Score : ", GLUT_BITMAP_TIMES_ROMAN_24);

	if (!best_score){
		iSetcolor(0, 127, 0);
		iText(830, 300, "0", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else{

		int rest = reverse(best_score);
		int dig = digit(best_score);
		char ch;
		int i = 830;
		int ret = rest;
		while (rest){

			ch = rest % 10 + 48;
			rest /= 10;
			iSetcolor(0, 127, 0);
			iText(i, 300, &ch, GLUT_BITMAP_TIMES_ROMAN_24);
			i += 10;
		}

		if (digit(ret) != dig){
			int diff = dig - digit(ret);
			while (diff--){
				iSetcolor(0, 127, 0);
				iText(i, 300, "0", GLUT_BITMAP_TIMES_ROMAN_24);
				i += 10;
			}
		}
	}

}

int addRandom()
{
	int dxx[16], dyy[16];
	int flag = 0;

	for (int i = 0; i<4; i++){
		for (int j = 0; j<4; j++){
			if (grid[i][j] == 0){
				dxx[flag] = i;
				dyy[flag++] = j;
			}
		}
	}

	dx = dxx[flag / 2];
	dy = dyy[flag / 2];

	return 2;
}

int gameOver()
{
	/*int flag = 0;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<3; j++)
		{
			if (grid[i][j] == grid[i][j + 1])
			{
				flag = 1;
				break;
			}
		}

		if (flag)
		{
			break;
		}

	}



	if (!flag)
	{
		for (j = 0; j <= 3; j++)
		{
			for (i = 0; i<3; i++)
			{
				if (grid[i][j] == grid[i + 1][j])
				{
					flag = 1;
					break;
				}
			}

			if (flag)
				break;

		}
	}
	if (flag)
		game_is_over = 0;
	else
		game_is_over = 1;
	return flag;*/
	bool ret = true;
	for (i = 0; i<4; i++){
		int kid = grid[i][0];
		for (j = 1; j<4; j++){
			if (grid[i][j]){
				if (grid[i][j] == kid){
					ret = false;
				}
				else
					kid = grid[i][j];
			}
			else
				ret = false;
		}
	}


	for (i = 0; i<4; i++){
		int kid = grid[0][i];
		for (j = 1; j<4; j++){
			if (grid[j][i]){
				if (grid[j][i] == kid){
					ret = false;
				}
				else
					kid = grid[j][i];
			}
			else
				ret = false;
		}
	}
	return ret;
}

void printNumber(int x, int y, int num)
{
	if (num == 2){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "2", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 4){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "4", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 8){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "8", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 16){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "16", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 32){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "32", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 64){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "64", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 128){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "128", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 256){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "256", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 512){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "512", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 1024){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "1024", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (num == 2048){
		iSetcolor(0, 0, 0);
		iText(x + 50, y + 50, "2048", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void printGrid()
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (grid[i][j] != 0){
				printNumber(200+i*120, 200+j*120, grid[i][j]);
			}
		}
	}
}

void inIt()
{
	addRandom();
	grid[dx][dy] = 2;
	
	addRandom();
	grid[dx][dy] = 2;
}

void moveUP()
{
	int temp, flag, cnt = 4, i, j;
	while (cnt)
	{
		for (j = 0; j <= 3; j++)
		{
			for (i = 3; i >= 1; i--)
			{
				if (!(grid[i - 1][j]))
				{
					//swap(ara[i][j], ara[i - 1][j]);
					temp = grid[i][j];
					grid[i][j] = grid[i - 1][j];
					grid[i - 1][j] = temp;
				}
			}
		}

		cnt--;
	}

	cnt = 4;

	for (j = 0; j <= 3; j++)
	{
		flag = 0;
		for (i = 3; i >= 1; i--)
		{
			if (!flag)
			{
				if (grid[i][j] == grid[i - 1][j])
				{
					grid[i - 1][j] = 2 * grid[i][j];
					grid[i][j] = 0;
					flag = 1;
					score += grid[i - 1][j];
				}
			}

			else
			{
				flag = 0;
			}
		}
	}

	while (cnt)
	{
		for (j = 0; j <= 3; j++)
		{
			for (i = 3; i >= 1; i--)
			{
				if (!(grid[i - 1][j]))
				{
					//swap(ara[i][j], ara[i - 1][j]);
					temp = grid[i][j];
					grid[i][j] = grid[i - 1][j];
					grid[i - 1][j] = temp;
				}
			}
		}

		cnt--;
	}
}

void moveDOWN()
{
	int temp, flag, cnt = 4, i, j;
	while (cnt)
	{
		for (j = 0; j <= 3; j++)
		{
			for (i = 0; i<3; i++)
			{
				if (!(grid[i + 1][j]))
				{
					//swap(ara[i][j], ara[i + 1][j]);
					temp = grid[i][j];
					grid[i][j] = grid[i+1][j];
					grid[i + 1][j] = temp;
				}
			}
		}

		cnt--;
	}

	cnt = 4;

	for (j = 0; j <= 3; j++)
	{
		flag = 0;
		for (i = 0; i<3; i++)
		{
			if (!flag)
			{
				if (grid[i][j] == grid[i + 1][j])
				{
					grid[i + 1][j] = 2 * grid[i][j];
					grid[i][j] = 0;
					flag = 1;
					score += grid[i + 1][j];
				}
			}

			else
			{
				flag = 0;
			}
		}
	}

	while (cnt)
	{
		for (j = 0; j <= 3; j++)
		{
			for (i = 0; i<3; i++)
			{
				if (!(grid[i + 1][j]))
				{
					//swap(ara[i][j], ara[i + 1][j]);
					temp = grid[i + 1][j];
					grid[i + 1][j] = grid[i][j];
					grid[i][j] = temp;
				}
			}
		}

		cnt--;
	}


}

void moveLEFT()
{
	int temp, flag, cnt = 4, i, j;
	while (cnt)
	{
		for (i = 0; i <= 3; i++)
		{
			for (j = 3; j >= 1; j--)
			{
				if (!(grid[i][j - 1]))
				{
					//swap(ara[i][j], ara[i][j - 1]);
					temp = grid[i][j];
					grid[i][j] = grid[i][j - 1];
					grid[i][j - 1] = temp;
				}
			}
		}

		cnt--;
	}



	cnt = 4;

	for (i = 0; i <= 3; i++)
	{
		flag = 0;
		for (j = 3; j >= 1; j--)
		{
			if (!flag)
			{
				if (grid[i][j] == grid[i][j - 1])
				{
					grid[i][j - 1] = 2 * grid[i][j];
					grid[i][j] = 0;
					flag = 1;
					score += grid[i][j-1];
				}
			}

			else
			{
				flag = 0;
			}
		}
	}


	while (cnt)
	{
		for (i = 0; i <= 3; i++)
		{
			for (j = 3; j >= 1; j--)
			{
				if (!(grid[i][j - 1]))
				{
					//swap(ara[i][j], ara[i][j - 1]);

					temp = grid[i][j];
					grid[i][j] = grid[i][j - 1];
					grid[i][j - 1] = temp;
				}
			}
		}

		cnt--;
	}



}

void moveRIGHT()
{
	int temp, flag, cnt = 4, i, j;
	while (cnt)
	{
		for (i = 0; i <= 3; i++)
		{
			for (j = 0; j<3; j++)
			{
				if (!(grid[i][j + 1]))
				{
					//swap(ara[i][j], ara[i][j + 1]);
					temp = grid[i][j];
					grid[i][j] = grid[i][j + 1];
					grid[i][j + 1] = temp;
				}
			}
		}

		cnt--;
	}


	cnt = 4;

	for (i = 0; i <= 3; i++)
	{
		flag = 0;
		for (j = 0; j<3; j++)
		{
			if (!flag)
			{
				if (grid[i][j] == grid[i][j + 1])
				{
					grid[i][j + 1] = 2 * grid[i][j];
					grid[i][j] = 0;
					flag = 1;
					score += grid[i][j+1];
				}
			}

			else
			{
				flag = 0;
			}
		}
	}


	while (cnt)
	{
		for (i = 0; i <= 3; i++)
		{
			for (j = 0; j<3; j++)
			{
				if (!(grid[i][j + 1]))
				{
					//swap(ara[i][j], ara[i][j + 1]);

					temp = grid[i][j];
					grid[i][j] = grid[i][j + 1];
					grid[i][j + 1] = temp;
				}
			}
		}

		cnt--;
	}


}

void time()
{
}
void mydelay(int mseconds)
{
	clock_t start, end;
	double elapsed;
	start = clock();
	while (1)
	{
		end = clock();
		elapsed = ((double)(end - start)) / ((double)CLOCKS_PER_SEC / 1000.0);
		if (elapsed>mseconds)break;
	}
}

void iKeyboard(unsigned char key)
{
	if (key == 'a')
		moveUP();
	else if (key == 's')
		moveLEFT();
	else if (key == 'd')
		moveDOWN();
	else if (key == 'w')
		moveRIGHT();

	addRandom();
	grid[dx][dy] = 2;
	//gameOver();
	if (gameOver()){
		game_is_over = 1;
	}
}

void iDraw()
{
	iClear();
	
	if (!game_is_started){
		inIt();
		game_is_started = 1;
	}

	
	if (!game_is_over){
		//iSetcolor(0, 0, 54);
		iSetcolor(156, 255, 188);
		iFilledRectangle(180, 180, 500, 500);
		int i, j;

		printScore();

		for (i = 200; i <= 560; i += 120){

			for (j = 200; j <= 560; j += 120){

				iSetcolor(54, 0, 0);
				iFilledRectangle(i, j, 100, 100);
			}
		}

		printGrid();
		bestScore();

	}
	else{
		iSetcolor(127, 0, 0);
		iText(400, 400, "Game Over", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{


}

void iPassiveMouseMove(int mx, int my)
{


}

/*void iKeyboard(unsigned char key)
{


}*/

void iSpecialKeyboard(unsigned char key)
{


}

int main()
{
	iSettimer(1000, time);
	iInitialize(1000, 1000, "Final");
	return 0;
}

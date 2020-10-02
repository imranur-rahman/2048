# include "iGraphics.h"
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
using namespace std;

#define BOUNDARY(i,j,k,l) ((mx>=i && mx<=j) && (my>=(1000-l) && my<=(1000-k)))
#define debug(a, b) printf("%d %d\n", a, b)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


int score = 0, flag = 0, textbox = 0, len, nameInput= 0, warning = 0, saving_game = 0, textboxVisited = 0, fileWarning = 0, hofShow = 0;
int game_is_over = 0, game_is_started = 0;
int i, j;
int d = 0;

int grid[4][4] = { 0 };
char saveFile[10], tempString[10];
int dx, dy;
char buffer[33];

struct game
{
	int slNo, score;
	char name[15];
} hof[15];

bool comp(game a, game b)
{
	if (a.score > b.score) return true;
	else return false;
}

void FileToStructureHOF()
{
	/*#pragma warning(push)
	#pragma warning(disable: 4996)
	FILE *fp;

	if ((fp = fopen("hall of fame.txt", "r")) == NULL)
	{
		fp = fopen("hall of fame.txt", "w");
		for (int i = 0; i < 11; i++)
			fprintf(fp, "%d EMPTY 0\n", i + 1);
		fclose(fp);
	}
	#pragma warning(pop)
	*/

	#pragma warning(push)
	#pragma warning(disable: 4996)
	FILE *fload;

	fload = fopen("hall of fame.txt", "r");
	for (int i = 0; i < 11; i++)
		fscanf(fload, "%d %s %d", &hof[i].slNo, hof[i].name, &hof[i].score);

	fclose(fload);
	#pragma warning(pop)
}

void StructureToFileHOF()
{

	#pragma warning(push)
	#pragma warning(disable: 4996)
	FILE *fsave;

	fsave = fopen("hall of fame.txt", "w");
	for (int i = 0; i < 11; i++)
		fprintf(fsave, "%d %s %d\n", i + 1, hof[i].name, hof[i].score);
	fclose(fsave);
	#pragma warning(pop)
}

void ToString(int n, char strOutput[])
{
	char str[100];
	int i;
	int temp;

	if (n == 0) { str[0] = '0'; str[1] = '\0'; }

	else if (n > 0)
	{
		for (i = 0, temp = n; temp != 0; temp /= 10)
			str[i++] = (temp % 10) + '0';

		str[i] = '\0';
		reverse(str, str + i);
	}

	else if (n < 0)
	{
		for (i = 0, temp = n * (-1); temp != 0; temp /= 10)
			str[i++] = (temp % 10) + '0';
		str[i] = '-';
		str[i + 1] = '\0';
		reverse(str, str + (i + 1));
	}
	#pragma warning(push)
	#pragma warning(disable: 4996)
	strcpy(strOutput, str);
	#pragma warning(pop)
}


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

void saveGame()
{
	ofstream fout("saved game.txt");
	
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			fout << grid[i][j] << " ";
		fout << endl;
	}

	fout << score;

	fclose(stdout);
}

void loadGame()
{
	ifstream fin("saved game.txt");

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			fin >> grid[i][j];
	}

	fin >> score;

	fclose(stdout);
}

void printScore()
{
	iSetcolor(255, 255, 255);
	iText(700, 200, "Score : ", GLUT_BITMAP_TIMES_ROMAN_24);

	/*itoa(score, buffer, 10);
	iSetcolor(0, 127, 0);
	iText(750, 200, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	buffer[33] = '\0';*/

	if (!score){
		iSetcolor(255, 255, 255);
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
			iSetcolor(255, 255, 255);
			iText(i, 200, &ch, GLUT_BITMAP_TIMES_ROMAN_24);
			i += 10;
		}

		if (digit(ret) != dig){
			int diff = dig - digit(ret);
			while (diff--){
				iSetcolor(255, 255, 255);
				iText(i, 200, "0", GLUT_BITMAP_TIMES_ROMAN_24);
				i += 10;
			}
		}
	}
}

void bestScore()
{
	
	ifstream fin("best_score");
	int best_score;
	
	fin >> best_score;
	fclose(stdout);

	if (score > best_score){
		
		ofstream fout("best_score");
		best_score = score;
		
		fout << best_score;
		fclose(stdout);
	}

	iSetcolor(255, 255, 255);
	iText(700, 300, "Best Score : ", GLUT_BITMAP_TIMES_ROMAN_24);

	if (!best_score){
		iSetcolor(255, 255, 255);
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
			iSetcolor(255, 255, 255);
			iText(i, 300, &ch, GLUT_BITMAP_TIMES_ROMAN_24);
			i += 10;
		}

		if (digit(ret) != dig){
			int diff = dig - digit(ret);
			while (diff--){
				iSetcolor(255, 255, 255);
				iText(i, 300, "0", GLUT_BITMAP_TIMES_ROMAN_24);
				i += 10;
			}
		}
	}

}

void addRandom()
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

	//dx = dxx[flag / 2];
	//dy = dyy[flag / 2];
	int res = rand() % flag;
	dx = dxx[res];
	dy = dyy[res];

	bool pickNumber = (rand() % 100) < 70;

	if (pickNumber){
		//grid[dx][dy] = 2;
		//for (int i = 0; i < 1e6; i++){}
		//iShowBMP(200 + dx * 120, 200 + dy * 120, "2.1.bmp");
		//printf("%d %d\n", 200 + dx * 120, 200 + dy * 120);
		//for (int i = 0; i < 1e8; i++){}
		//iShowBMP(dx, dy, "2.bmp");
		grid[dx][dy] = 2;
	}
	else
		grid[dx][dy] = 4;
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
	if (num == 0)
		iShowBMP(x, y, "blue.bmp");
	if (num == 2){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "2", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "2.bmp");
	}
	else if (num == 4){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "4", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "4.bmp");
	}
	else if (num == 8){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "8", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "8.bmp");
	}
	else if (num == 16){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "16", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "16.bmp");
	}
	else if (num == 32){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "32", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "32.bmp");
	}
	else if (num == 64){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "64", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "64.bmp");
	}
	else if (num == 128){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "128", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "128.bmp");
	}
	else if (num == 256){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "256", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "256.bmp");
	}
	else if (num == 512){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "512", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "512.bmp");
	}
	else if (num == 1024){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "1024", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "1024.bmp");
	}
	else if (num == 2048){
		//iSetcolor(0, 0, 0);
		//iText(x + 50, y + 50, "2048", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(x, y, "2048.bmp");
	}
}

void printGrid()
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			//if (grid[i][j] != 0){
				printNumber(200+i*120, 200+j*120, grid[i][j]);
			//}
		}
	}
}

void inIt()
{
	addRandom();
	
	addRandom();
	
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
		//flag = 0;
		for (i =0; i<3; i++)
		{
			//if (!flag)
			
				if (grid[i][j] == grid[i+1][j])
				{
					grid[i][j] = 2 * grid[i+1][j];
					grid[i+1][j] = 0;
					//flag = 1;
					score += grid[i][j];
				}
			

			//else
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
		for (i = 3; i>0; i--)
		{
			//if (!flag)
			
				if (grid[i][j] == grid[i-1][j])
				{
					grid[i][j] = 2 * grid[i-1][j];
					grid[i-1][j] = 0;
					//flag = 1;
					score += grid[i][j];
				}
			

			//else
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
		//flag = 0;
		for (j = 0; j<3; j++)
		{
			//if (!flag)
			{
				if (grid[i][j] == grid[i][j+1])
				{
					grid[i][j] = 2 * grid[i][j+1];
					grid[i][j+1] = 0;
					//flag = 1;
					score += grid[i][j];
				}
			}

			//else
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
		//flag = 0;
		for (j = 3; j>0; j--)
		{
			//if (!flag)
			
				if (grid[i][j] == grid[i][j-1])
				{
					grid[i][j] = 2 * grid[i][j-1];
					grid[i][j-1] = 0;
					//flag = 1;
					score += grid[i][j];
				}
			

			//else
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

void nameForFame()
{
	iShowBMP(0, 0, "name input 1.bmp");

	if (textbox == 1)
	{
		iShowBMP(0, 0, "name input 2.bmp");
		iSetcolor(255, 0, 43);
		iText(380, 750, saveFile, GLUT_BITMAP_TIMES_ROMAN_24);
		#pragma warning(push)
		#pragma warning(disable: 4996)
		strcpy(hof[10].name, saveFile);
		#pragma warning(pop)
		textboxVisited = 1;
	}

	if (warning == 1)
	{
		iSetcolor(255, 2, 0);
		//iText(350, 637, "Sorry dude! No SPACE allowed!", GLUT_BITMAP_TIMES_ROMAN_24);
		//iText(360, 600, "You can use underscore(_) instead.", GLUT_BITMAP_HELVETICA_18);
		iShowBMP(300, 213, "Batman-Slapping-Robin.bmp");
	}

	if (textbox == 0 && textboxVisited == 1)
	{
		sort(hof, hof + 11, comp);
		StructureToFileHOF();

		warning = 0;
		fileWarning = 0;
		nameInput = 0;
		textboxVisited = 0;
		hofShow = 1;
	}
}

void hofStart()
{
	iSetcolor(255, 255, 255);
	iFilledRectangle(0, 0, 1000, 1000);
	//iShowBMP(0, 0, "")
	iShowBMP(200, i, "wwf.bmp");
	i+=2;
	if (i > 1000)
	{
		i = 0;
		hofShow = 2;
	}
} 

void hallOfFameWindow()
{
	/*if (fileWarning == 0)
	{
		FileToStructureHOF();
		fileWarning = 1;
	}*/

	FileToStructureHOF();

	iShowBMP(0, 0, "hof.bmp");

	iSetcolor(255, 255, 255);
	iText(280, 650, "Serial", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(380, 650, "NAME", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(480, 650, "SCORE", GLUT_BITMAP_TIMES_ROMAN_24);



	iSetcolor(100, 100, 0);
	ToString(hof[0].slNo, tempString);
	iText(280, 600, tempString, GLUT_BITMAP_HELVETICA_18);
	iText(380, 600, hof[0].name, GLUT_BITMAP_HELVETICA_18);
	ToString(hof[0].score, tempString);
	iText(480, 600, tempString, GLUT_BITMAP_TIMES_ROMAN_24);



	iSetcolor(0, 100, 100);
	for (int i = 1, h = 550; i < 10; i++, h -= 40)
	{
		hof[i].slNo = i + 1;
		ToString(hof[i].slNo, tempString);
		iText(280, h, tempString, GLUT_BITMAP_HELVETICA_18);
	}


	for (int i = 1, h = 550; i < 10; i++, h -= 40)
		iText(380, h, hof[i].name, GLUT_BITMAP_HELVETICA_18);


	for (int i = 1, h = 550; i < 10; i++, h -= 40)
	{
		ToString(hof[i].score, tempString);
		iText(480, h, tempString, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	/*if (clicked == 1)
	{
		hofShow = 0;
		clicked = 0;
		//startMenuCmpltd = 0;
		//newInit = 0;
		game_is_started = 0;
		game_is_over = 0;
	}*/

	for (int i = 0; i < 11; i++)
		printf("%d %s %d\n", &hof[i].slNo, hof[i].name, &hof[i].score);
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
	if (game_is_started == 1 && game_is_over == 0)
	{
		if (key == 'a')
			moveUP(), printGrid(), addRandom();
		else if (key == 's')
			moveLEFT(), printGrid(), addRandom();
		else if (key == 'd')
			moveDOWN(), printGrid(), addRandom();
		else if (key == 'w')
			moveRIGHT(), printGrid(), addRandom();
	}

	if (textbox == 1)
	{
		if (nameInput == 1 && key == '\r')
		{
			textbox = 0;

			for (int i = 0; i < len; i++)
				saveFile[i] = 0;
			len = 0;
			//textboxVisited = 1;

		}

		if (key == '\b' && len > 0)
		{
			len--;
			saveFile[len] = '\0';
		}

		else if (key == 32) // Spacebar Pressed
		{
			if (saving_game == 1 || nameInput == 1)
			{
				warning = 1;
			}
		}

		else if (len < 10)
		{
			saveFile[len] = key;
			len++;
		}
	}

	/*else if (key == 'f'){
		if (!game_is_started)
			inIt(), game_is_started = 1;
	}
	else if (key == 'g'){
		if (!game_is_started)
			loadGame(), game_is_started = 1;
	}*/
	//printGrid();
	//iDraw();
	//mydelay(500);
	
	
	//printGrid();
	//gameOver();
	//iDraw();
	
	/*if (gameOver()){
		game_is_over = 1;
		game_is_started = 0;
	}
	else
		saveGame();
	*/
}

void iDraw()
{
	iClear();
	
	if (!game_is_started && hofShow == 0){
		iShowBMP(0, 0, "New Background.bmp");
		//inIt();
		//game_is_started = 1;
	}

	
	if (!game_is_over  &&  game_is_started){
		//iSetcolor(0, 0, 54);
		iShowBMP(0, 0, "Purple.bmp");
		//iSetcolor(0, 0, 0);
		//iFilledRectangle(180, 180, 500, 500);
		iShowBMP(180, 180, "ash.bmp");
		int i, j;

		printScore();

		for (i = 200; i <= 560; i += 120){

			for (j = 200; j <= 560; j += 120){

				iSetcolor(127, 127, 127);
				iFilledRectangle(i, j, 100, 100);
			}
		}

		printGrid();
		bestScore();

		if (gameOver()){
			game_is_over = 1;
			game_is_started = 0;
		}
		else
			saveGame();
		
	}
	if(game_is_over  && hofShow == 0){
		//iSetcolor(127, 0, 0);
		//iText(400, 400, "Game Over", GLUT_BITMAP_TIMES_ROMAN_24);
		//iInitialize(500, 500, "Game Over");
		
		if (nameInput == 0)
		{
			//printGrid();
			/*for (int i = 0; i < 100000; i++){

			}*/

			//iShowBMP(0, 0, "gameOver.bmp");
			iShowBMP(0, 0, "troll.bmp");
			/*for (int i = 0; i < 1000000000; i++){

			}*/
			
			if (d > 3){
				nameInput = 1;
				d = 0;
				
				FileToStructureHOF();
				sort(hof, hof + 11, comp);

				if (hof[9].score < score)
				{
					hof[10].score = score;
				}

			}
			else
				d++;
			
		}
		else
		{
			nameInput = 1;
			nameForFame();
		}
		//nameInput = 1;
		//nameForFame();
	}
	if (hofShow == 1)
	{
		hofStart();
	}
	if (hofShow == 2)
	{
		sort(hof, hof + 11, comp);
		StructureToFileHOF();

		warning = 0;
		fileWarning = 0;
		nameInput = 0;
		textboxVisited = 0;
		//hofShow = 1;

		hallOfFameWindow();
	}
	if (textbox == 0 && textboxVisited == 1)
	{
		sort(hof, hof + 11, comp);
		StructureToFileHOF();

		warning = 0;
		fileWarning = 0;
		nameInput = 0;
		textboxVisited = 0;
		hofShow = 1;
	}
	//FileToStructureHOF();
}

void iMouseMove(int mx, int my)
{
	
}


void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d %d\n", mx, my);
		if (game_is_started == 0  && game_is_over == 0)
		{
			if (BOUNDARY(120, 388, 162, 222))
			{
				inIt();
				game_is_started = 1;
			}
			else if (BOUNDARY(516, 769, 162, 222))
			{
				loadGame();
				game_is_started = 1;
			}
			else if (BOUNDARY(291, 641, 287, 380))
			{
				hofShow = 1;
			}
		}

		if (nameInput == 1)
		{
			
			if (BOUNDARY(338, 675, 175, 224))
			{
				
				textbox = 1;
			}
		}

		
	}

	
}

void iPassiveMouseMove(int mx, int my)
{


}

/*void iKeyboard(unsigned char key)
{


}*/

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here

	/*if (game_is_started == 1 && game_is_over == 0)
	{
		if (key == GLUT_KEY_LEFT) moveUP(), printGrid(), addRandom();
		else if (key == GLUT_KEY_RIGHT) moveDOWN(), printGrid(), addRandom();
		else if (key == GLUT_KEY_DOWN) moveLEFT(), printGrid(), addRandom();
		else if (key == GLUT_KEY_UP) moveRIGHT(), printGrid(), addRandom();
	}*/
}

int main()
{
	iSettimer(1000, time);
	iInitialize(1000, 1000, "Final");
	return 0;
}

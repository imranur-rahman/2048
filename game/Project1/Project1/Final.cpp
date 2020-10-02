# include "iGraphics.h"

int ct=0;
int x=5;
int flag=0;

void time()
{
}
void mydelay(int mseconds)
{
	clock_t start, end;
	double elapsed;
	start = clock();
	while(1)
	{
		end = clock();
		elapsed = ((double) (end - start)) / ((double)CLOCKS_PER_SEC/1000.0);
		if(elapsed>mseconds)break;
	}
}
void iDraw()
{
	iClear();
	iSetcolor(255,255,255);
	//iFilledRectangle(ct,ct,ct,20);
	
	//iSetColor(0,255,0);		
	//iLine(0,0,500,500);
	//ct++;
	//mydelay(100);
	iFilledCircle(x, 100,16,100);
	if(flag==0)
	{
		if(ct%3==0) x++;
			ct++;
		if(x==500) flag=1;
	}
	else
	{
		if(ct%3==0) x--;
		ct++;
		if(x==10) flag=0;
	}
	//iText(25,575,"Hello World",GLUT_BITMAP_TIMES_ROMAN_24);
	
}

void iMouseMove(int mx, int my)
{
}	

void iMouse(int button, int state, int mx, int my)
{

	
}

void iPassiveMouseMove(int mx,int my)
{
	

}

void iKeyboard(unsigned char key)
{

	
}

void iSpecialKeyboard(unsigned char key)
{

	
}

int main()
{
	iSettimer(1000, time);
	iInitialize(800, 600, "Final");
	return 0;
}

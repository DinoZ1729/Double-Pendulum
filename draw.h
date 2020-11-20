#include <iostream>
#include <windows.h>

constexpr int WIDTH = 1000,HEIGHT = 600;
constexpr int dW=8,dH=16;

void gotoxy ( short x, short y )
{
COORD coord = {x, y};
SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

void plotLineLow(char platno[HEIGHT/dH][WIDTH/dW+1],int x0,int y0,int x1,int y1,char c);
void plotLineHigh(char platno[HEIGHT/dH][WIDTH/dW+1],int x0,int y0,int x1,int y1,char c);
void drawPoint(char platno[HEIGHT/dH][WIDTH/dW+1],int A,int B,char c);
void drawLine(char platno[HEIGHT/dH][WIDTH/dW+1],int A,int B,int C,int D,char c);

void drawPoint(char platno[HEIGHT/dH][WIDTH/dW+1],int A,int B,char c)
{
	if(A<0||B<0||A>=WIDTH/dW||B>=HEIGHT/dH)	return;
	platno[B][A]=c;
}

void drawLine(char platno[HEIGHT/dH][WIDTH/dW+1],int A,int B,int C,int D,char c)
{
	//sorting
	if(A>C)
	{
		int t;
		t=A;
		A=C;
		C=t;
		t=B;
		B=D;
		D=t;
	}
	//algorithm
	if(B==D)
	{
		for(int i=A;i<=C;i++)
			drawPoint(platno,i,B,c);//platno[B][i]=c;
		return;
	}
	if(A==C)
	{
		int min=B,max=D;
		if(D<B)
		{
			min=D;
			max=B;
		}
		for(int i=min;i<=max;i++)
			drawPoint(platno,A,i,c);//platno[i][A]=c;
		return;
	}
	if(abs(D-B)<abs(C-A))
		plotLineLow(platno,A,B,C,D,c);
	else
	{
		if(B>D)	plotLineHigh(platno,C,D,A,B,c);
		else	plotLineHigh(platno,A,B,C,D,c);
	}
}

void plotLineLow(char platno[HEIGHT/dH][WIDTH/dW+1],int x0,int y0,int x1,int y1,char c)
{
    int dx = x1 - x0, dy = y1 - y0, yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
	}
    int D = 2*dy - dx;
    int y = y0;

    for (int x=x0;x<=x1;x++)
    {
        drawPoint(platno,x,y,c);
        if( D > 0)
        {
            y += yi;
            D -= 2*dx;
		}
        D += 2*dy;
	}
}

void plotLineHigh(char platno[HEIGHT/dH][WIDTH/dW+1],int x0,int y0,int x1,int y1,char c)
{
    int dx = x1 - x0, dy = y1 - y0, xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
	}
    int D = 2*dx - dy;
    int x = x0;

    for (int y=y0;y<=y1;y++)
    {
        drawPoint(platno,x,y,c);
		if( D > 0)
        {
            x += xi;
            D -= 2*dy;
		}
        D += 2*dx;
	}
}

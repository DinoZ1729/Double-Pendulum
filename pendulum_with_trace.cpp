#include <iostream>
#include "draw.h"
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#define M_PI 3.14159265358979323846
using namespace std;

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    float elapsed() const { 
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<float, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

int main()
{
	float 
	l1,l2,	//lengths
	m1,m2,	//masses
	O1,O2,	//angles
	w1,w2,	//angular velocities
	g=9.81f;
	
	l1=150.0f;
	l2=150.0f;
	m1=10.0f;
	m2=10.0f;
	O1=2.0f*M_PI/2.0f;
	O2=2.0f*M_PI/3.0f;
	w1=0.0f;
	w2=0.0f;
	
	//time
	const float fps=300.0f;
	const float dt=1.0f/fps;
	float accumulator = 0.0f;
	Timer tmr;
	float frameStart=tmr.elapsed();
	
	char platno[HEIGHT/dH][WIDTH/dW+1];
	for(int i=0;i<HEIGHT/dH-1;i++)	platno[i][WIDTH/dW]='\n';
	platno[HEIGHT/dH-1][WIDTH/dW]='\0';
	for(int i=0;i<HEIGHT/dH;i++)
	{
		for(int j=0;j<WIDTH/dW;j++)
		{
			platno[i][j]=' ';
		}
	}
	
	int trace[HEIGHT/dH][WIDTH/dW];
	for(int i=0;i<HEIGHT/dH;i++)
	{
		for(int j=0;j<WIDTH/dW;j++)
		{
			trace[i][j]=0;
		}
	}
	
	//main loop
	while(true)
	{
		gotoxy(0,0);
		//time
		float currentTime=tmr.elapsed();
		accumulator+=currentTime-frameStart;
		
		frameStart=currentTime;
		
		
		if(accumulator>=1.0f/30.0f)	accumulator=1.0f/30.0f;
		
		while(accumulator > dt)
		{
			//just trust the formulas
			float
			alfa1=(  -g*(2*m1 +m2 )*sin(O1 )-g*m2 *sin(O1 -2*O2 )-2*m2 *sin(O1 -O2 )*(w2 *w2 *l2 +w1 *w1 *l1 *cos(O1 -O2 ))  )/(  l1 *(2*m1 +m2 -m2 *cos(2*O1 -2*O2 ))  ),
			alfa2=(  2*sin(O1 -O2 )  )*(  w1 *w1 *l1 *(m1 +m2 ) + g*(m1 +m2 )*cos(O1 ) + w2 *w2 *l2 *m2 *cos(O1 -O2 )  )/l2 /(  2*m1 +m2 -m2 *cos(2*O1 -2*O2 )  );
			
			//time is sped up 10 times for better effect
			w1 +=10*dt*alfa1;
			w2 +=10*dt*alfa2;
			O1 +=10*dt*w1;
			O2 +=10*dt*w2;
				
			
			accumulator-=dt;
			
			for(int i=0;i<HEIGHT/dH;i++)
			{
				for(int j=0;j<WIDTH/dW;j++)
				{
					if(trace[i][j]>0)	trace[i][j]--;	
				}
			}	
		}
		
		//drawing
		for(int i=0;i<HEIGHT/dH;i++)
		{
			for(int j=0;j<WIDTH/dW;j++)
			{
				
				if(platno[i][j]=='@')	trace[i][j]=fps;
				
				if(trace[i][j]>=3*(int)fps/4)	platno[i][j]=':';
				else if(trace[i][j]>=2*(int)fps/4)	platno[i][j]='.';
				else if(trace[i][j]>=(int)fps/4)	(i+j)%2?platno[i][j]='.':platno[i][j]=' ';
				else	platno[i][j]=' ';
			}
		}
		
		int x1=(WIDTH/2+sin(O1)*l1+dW*0.5f)/dW;
		int y1=(cos(O1)*l1+dH*0.5f)/dH+HEIGHT/dH/2;
		
		int x2=x1+(sin(O2)*l2+dW*0.5f)/dW;
		int y2=y1+(cos(O2)*l2+dH*0.5f)/dH;
		
		drawLine(platno,WIDTH/2/dW,HEIGHT/dH/2,x1,y1,'#');
		drawLine(platno,x1,y1,x2,y2,'#');
		
		drawPoint(platno,WIDTH/2/dW,HEIGHT/dH/2,'O');
		drawPoint(platno,x1,y1,'@');
		drawPoint(platno,x2,y2,'@');
		
		puts(platno[0]);
	}
	return 0;
	
}

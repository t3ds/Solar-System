#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<stdbool.h>
#include<windows.h>

#define pi 3.14159
//initializing control parameters
int basesize;
int xinc;
int yinc;

void drawplanet(int time,double rel_time,int size,int orbit,int color)
{
	int rx,ry,degree,x,y;
	float temp;
	temp=time*rel_time;

	degree=(int)temp%360;

	rx=(basesize+xinc*orbit);
	ry=(basesize+yinc*orbit);

	x=rx*cos(degree*(pi/180));
	y=ry*sin(degree*(pi/180));
	circle((getmaxx()/2)+x,(getmaxy()/2)+y,size);

	setfillstyle(1,color);
	floodfill((getmaxx()/2)+x,(getmaxy()/2)+y,WHITE);

}

void draw_solar(double rel_time[],int size[],int orbit[],int time,int color[])
{
    int rx,ry,i;

    //SUN
    setfillstyle(1,YELLOW);
    circle((getmaxx()/2),(getmaxy()/2),basesize);
    floodfill((getmaxx()/2),(getmaxy()/2),WHITE);

    //ORBITS
    setcolor(YELLOW);
    for(i=0;i<8;i++)
    {
        rx=basesize+xinc*(i+1);
        ry=basesize+yinc*(i+1);
        ellipse((getmaxx()/2),(getmaxy()/2),0,360,rx,ry);
    }

    setcolor(WHITE);
    for(i=0;i<8;i++)
    {
        drawplanet(time,rel_time[i],size[i],orbit[i],color[i]);
    }
}
int main()
{       //normal stuff
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	double rel_time[8];
	int size[8],orbit[8],color[8];

	//time taken for 1 revolution around the sun
	//for revolution logic
	rel_time[0]=365.26/87.96;
	rel_time[1]=365.26/244.86;
	rel_time[2]=1;
	rel_time[3]=365.26/686.98;
	rel_time[4]=1/11.862;
	rel_time[5]=1/29.456;
	rel_time[6]=1/84.07;
	rel_time[7]=1/164.81;

	//relative planet sizes,can be changed as per our wish
	size[0]=4;
	size[1]=9;
	size[2]=10;
	size[3]=7;
	size[4]=19;
	size[5]=15;
	size[6]=11;
	size[7]=11;

	//orbit sizes
	orbit[0]=1;
	orbit[1]=2;
	orbit[2]=3;
	orbit[3]=4;
	orbit[4]=5;
	orbit[5]=6;
	orbit[6]=7;
	orbit[7]=8;

	color[0]=7;
	color[1]=12;
	color[2]=1;
	color[3]=4;
	color[4]=10;
	color[5]=6;
	color[6]=3;
	color[7]=9;


	//control parameters for size of orbits and planets and stuff
	//basesize for size of sun
	//xinc and yinc for difference in x and y radius for each successive orbit
	basesize=40;
	xinc=28;
	yinc=19;


	int time,flag;
	bool key=true;
	flag=0;
	time=0;

	//infinite loop till escape is pressed because turboc wont exit out of an infinite loop
	while(key)
	{
	    if(GetAsyncKeyState(VK_ESCAPE))
            key=false;
        else
        {
            //for double buffering
            setactivepage(flag);
            setvisualpage(1-flag);
            cleardevice();

            draw_solar(rel_time,size,orbit,time,color);
            time++;
            flag=1-flag;
            delay(10);
        }

	}

	getch();
	closegraph();
	return 0;
}

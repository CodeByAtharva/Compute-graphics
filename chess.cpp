#include<iostream>
#include<GL/glut.h>
#include<math.h>
using namespace std;
#define w 640
#define h 480

float boundaryColor[3]={1,0,0},interiorColor[3]={1,1,1},fillColor[3]={0,0,0},readpixel[3];
int X,Y;
void setpixel(int x,int y)
{
	glColor3fv(fillColor);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();
}
void getpixel(int x,int y,float *color)
{
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}

void myInit(void)
{
   glClearColor(1.0,1.0,1.0,0.0);
   glColor3f(0.0f,0.0f,0.0f);
   glClear(GL_COLOR_BUFFER_BIT);
 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,w,0,h);
}
void plot(float x,float y)
{
  
    glBegin(GL_POINTS);
    
    glVertex2f(x,y);
    glEnd();
    glFlush();
}
int sign(float val)
{
    if(val<0)
    {
       return -1;
    }
    if(val>0)
    {
       return 1;
    }
    else
    {
       return 0;
    }
}
void Bresenham(int x1,int y1,int x2,int y2)
{
   int x,y,dx,dy,temp,e;
   int s1,s2,interchange,i;
   
   x=x1;
   y=y1;
   dx=abs(x2-x1);
   dy=abs(y2-y1);
   s1=sign(x2-x1);
   s2=sign(y2-y1);
   
   if(dy>dx)
   {
      temp=dx;
      dx=dy;
      dy=temp;
      interchange=1;
   }
   else
   {
      interchange=0;
   }
   e=2*dy-dx;
   for(i=1;i<dx;i++)
   {
       plot(x,y);
       while(e>=0)
       {
           if(interchange==1)
           {
               x=x+s1;
           }
           else
           {
               y=y+s2;
           }
           e=e-2*dx;
       }
       if(interchange==1)
          y=y+s2;
       else
          x=x+s1;
       e=e+2*dy;
    }
    
}

void rotate(int x1,int y1,int x2,int y2)
{
   int p1,q1,p2,q2;
   float angle;
   angle=45;
   angle=(3.14*angle)/180;
   p1=x1*cos(angle)+y1*sin(angle);
   q1=x1*sin(-angle)+y1*cos(angle);
   p2=x2*cos(angle)+y2*sin(angle);
   q2=x2*sin(-angle)+y2*cos(angle);
   
   Bresenham(p1,q1,p2,q2);
}
void floodfill(int x,int y)
{
	getpixel(x,y,readpixel);
	if(readpixel[0]==interiorColor[0] && readpixel[1]==interiorColor[1] && readpixel[2]==interiorColor[2])
	{
		setpixel(x,y);
		floodfill(x+1,y);
		floodfill(x,y+1);
		floodfill(x-1,y);
		floodfill(x,y-1);
		glEnd();
		glFlush();
	}
}

void create_menu(int item)
{
   if(item==1)
   {
        Bresenham(200,300,302,300);
	Bresenham(300,300,300,402);
	Bresenham(300,400,198,400);
	Bresenham(200,400,200,298);
	Bresenham(200,325,302,325);
	Bresenham(200,350,302,350);
	Bresenham(200,375,302,375);
	Bresenham(225,300,225,402);
	Bresenham(250,300,250,402);
	Bresenham(275,300,275,402);
	


   }
   if(item==2)
   {
        
        rotate(200,300,302,300);
	rotate(300,300,300,402);
	rotate(300,400,198,400);
	rotate(200,400,200,298);
	rotate(200,325,302,325);
	rotate(200,350,302,350);
	rotate(200,375,302,375);
	rotate(225,300,225,402);
	rotate(250,300,250,402);
	rotate(275,300,275,402);
     
   }
}


void mouseClick(int button,int state,int x,int y)
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
	{
		X=x;
		Y=480-y;
		floodfill(X,Y);
	}
}
  
     

void myDisplay(void)
{
    
        glClear(GL_COLOR_BUFFER_BIT);
        glEnd();
        glFlush(); 
} 

int main(int argc,char **argv)
{
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    
    glutCreateWindow("CHESS BOARD");
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouseClick);
    glutCreateMenu(create_menu);
    glutAddMenuEntry("DRAW CHESSBOARD",1);
    glutAddMenuEntry("ROTATE CHESSBOARD",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    myInit();
    glutMainLoop();
   return 0;
}      


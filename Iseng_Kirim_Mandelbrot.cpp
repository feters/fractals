#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include <windows.h>
#include <math.h>
#include <iostream>

using namespace std;

float merah=0.0f, hijau=0.1f, biru=0.1f;
float outmerah=0.0f, outhijau=0.1f, outbiru=0.1f;
int style=1;
//mendefinisikan warna red, green, dan blue untuk pixel
struct tipe_warna{
	float r;
	float g;
	float b;
};

//inisialisasi ukuran window 640x481
int abc=481;
int defi=640;
//membuat variable pixel yang berisi warna
//pattern
struct tipe_warna pixels[481*640], pattern[999];

void mandelbrotset()
{
	float x0,y0,x,y,xtemp;
	int iterasi, maks_iterasi, ploc=0;

/*
mandelbrot set function : f(x)=z^2+c
x0 : bilangan real bagian dari c
y0 : bilangan imaginer bagian dari c
x dan y : bilangan real dan imaginer dalam z ke-n
ploc : pixel location kordinat xy
*/

	for(y0=-0.7; y0<0.7; y0=y0+(1.4/abc))
	{
		for(x0=-1.5; x0<0.1; x0=x0+(1.6/defi))
		{
			x=0;
			y=0;
			iterasi=0;
			maks_iterasi=1000;

			while(((x*x)+(y*y)<(2*2)) && iterasi < maks_iterasi)
			{
				if(style==1){
					xtemp = (x*x) - (y*y) + x0;
	   				y = (2*x*y) + y0;
				}
	   			else if(style==2){
					 xtemp = (x*x)*y - (y*y)*x + x0;
					 y = (2*x*y) + y0;
				}
				else if(style==3){
					 xtemp = (x*x) - (y*y) + x0;
					 x = (2*x*y) + y0;
				}
				else if(style==4){
					 xtemp = (x*y) - (y*y) + x0;
					 y = (2*x*y) + y0;
				}
			x=xtemp;
			iterasi++;
			}
			if(iterasi>=999)
			{
				if(style==2|| style==3){
					pixels[ploc].r=0;
					pixels[ploc].g=x;
					pixels[ploc].b=y;
				}
				else if(style==1||style==4){
					pixels[ploc].r=merah;
					pixels[ploc].g=hijau;
					pixels[ploc].b=biru;
				}
			}
			else
			{
				pixels[ploc].r=pattern[iterasi].r;
				pixels[ploc].g=pattern[iterasi].g;
				pixels[ploc].b=pattern[iterasi].b;
			}
			ploc++;
		}
	}
}

void draw()
{
    int i;
   float r, g, b;

   for(i = 0; i < 481*640; i++){
      pixels[i].r = 1;
      pixels[i].g = 1;
      pixels[i].b = 1;
   }
   i=0;

   for(r = 0.1; r <= 0.9; r= r+r*r)
   {
   	for(g = 0.1; g <= 0.9; g = g+2*r*g)
   	{
   		for(b = 0.1; b <= 0.9; b = b+4*g*b)
		{
            pattern[i].r = b+outmerah;
            pattern[i].g = r+outhijau;
            pattern[i].b = g+outbiru;
            i++;
        }
   	}
   }

   for( ; i <= 999; i++){
      pattern[i].r = 1;
      pattern[i].g = 1;
      pattern[i].b = 1;
   }
   mandelbrotset();
}

void Init()
{
   glViewport(0, 0, 640, 481);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity( );
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluOrtho2D(0, 640, 0, 481);

   draw();
}

void onDisplay()
{
/*
* Clearing the initial buffer
*/
   glClearColor(1, 1, 1, 0);
   glClear(GL_COLOR_BUFFER_BIT);
/*
* Draw the complete Mandelbrot set picture.
*/
   glDrawPixels(640, 481, GL_RGB, GL_FLOAT, pixels);
   glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key){
    case 'q':
        exit(0);
    
    case 'r':
		merah=merah+0.2;
		mandelbrotset();
		glutPostRedisplay();
    	break;
    
    case 'g':
		hijau=hijau+0.2;
		mandelbrotset();
		glutPostRedisplay();
		break;
		
    case 'b':
		biru=biru+0.2;
		mandelbrotset();
		glutPostRedisplay();
		break;
		
    case 'd':
		merah=0.0;
		hijau=0.1;
		biru=0.1;
		outmerah=0.0;
		outhijau=0.1;
		outbiru=0.1;
		mandelbrotset();
		glutPostRedisplay();
		break;
		
    case 'i':
		outmerah=outmerah+0.4;
		draw();
		glutPostRedisplay();
		break;
	
    case 'j':
		outhijau=outhijau+0.4;
		draw();
		glutPostRedisplay();
		break;
		
    case 'n':
		outbiru=outbiru+0.4;
		draw();
		glutPostRedisplay();
		break;
	
	case '1':
		style=1;
		mandelbrotset();
		glutPostRedisplay();
		break;
	
	case '2':
		style=2;
		mandelbrotset();
		glutPostRedisplay();
		break;	

	case '3':
		style=3;
		mandelbrotset();
		glutPostRedisplay();
		break;
		
	case '4':
		style=4;
		mandelbrotset();
		glutPostRedisplay();
		break;

    default:
        glutIdleFunc(NULL);
        return;
    }
    glutPostRedisplay();
}

void usage()
{
    cout << "\n\
-----------------------------------------------------------------------\n\
  Inputs:\n\
    colour inputs:(only change style 1)\n\
    inner colours\n\
    r:	increase inner red colour value\n\
    g:	increase inner green colour value\n\
    b:	increase inner blue colour value\n\
    \n\
    outer colours\n\
    i:	increase outer red colour value\n\
    j:	increase outer green colour value\n\
    n:	increase outer blue colour value\n\
    \n\
    set to default settings\n\
    d:	return to default(style 1, r=0, g=0.1, b=0.1)\n\
    \n\
    style inputs:\n\
    1:	mandelbrot default\n\
    2:	style 2\n\
    3:	style 3\n\
    4:	style 4\n\
	\n\
    Quit program\n\
    q:	Quit\n\
  Place the cursor over the graphics window for\n\
  keyboard input to be processed.\n\
-----------------------------------------------------------------------\n";
    cout.flush();
}

int main(int argc, char** argv)
{
	usage();
    glutInit(&argc, argv);
    glutInitWindowSize (640, 481);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Mandelbrotset");
	glutKeyboardFunc(keyboard);
    Init ();

    glutDisplayFunc(onDisplay);
    glutMainLoop();
    return 0;
}

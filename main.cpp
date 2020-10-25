#include <windows.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <unistd.h>
#include "Headers/TexLoader.h"
#include "Headers/MTL_Loader.h"
#include "Headers/OBJ_Loader.h"
#include "Headers/StlLoader.h"
#include "Headers/ScreenShot.h"
#include "Headers/File.Dialog.h"

float Width, Height;

//****NO START****//
float zoom = 14.5;
//Cam Pos
float CPX = 0.0;
float CPY = 0.0;
float CPZ = 0.0;
//Cam Rot
float CRX = 40.0;
float CRY = -35.0;
float CRZ = 0.0;
//Mouse Wheel
bool MWP = false;
//****NO START****//

//****START****//
//Cam Pos
float SCPX = 20.0;
float SCPY = 1.0;
float SCPZ = 6.0; 
float deltaX = 0.0;
float deltaY = 0.0;
float deltaZ = 0.0;
//Cam Rot
float SCRX = 0.0;
float SCRY = 0.0;
float SCRZ = 0.0; 

float lx=0.0f,ly=0.0f,lz=0.0f;
//****START****//

float FOV = 60.0;

bool Start = false;

//Objects
int PC = 0;
int CC = 0;
int SC = 0;
int COC = 0;
int TC = 0;
int MC = 0;
int CYC = 0;

float PlanS = 1.0;
bool PS = false; 

bool ArrowC = false;

bool Light = true;
bool Shadows = true; 
bool ShadeSmooth = true;
float LightPosX = 3.0;
float LightPosY = 5.0;
float LightPosZ = -3.0;
#include "Headers/Stencil_Shadow.h"

int StartCam = 0;
int deltaStartCam = 0;

//Wire Mode
int Poly = 0;
int deltaPoly = 0;

#include "Headers/Read.Write.h"
#include "Headers/Menu.h"

void Resize(int w, int h)
{
	/**** Window Resize Func ****/
	Width = (float)w;
	Height = (float)h;
	float aspect = w*1.0/h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
//	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.1, 100000.0);
	gluPerspective(FOV, aspect, 0.1, 100000.0);
//	glOrtho(-3.0, 3.0, -2.0, 2.0, -1.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND); 		//enable alpha blending
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Layout()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, Width, Height, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
		glVertex2f(Width, Height/2);
		glVertex2f(Width, 0.0);
		glVertex2f(Width/1.25, 0.0);
		glVertex2f(Width/1.25, Height/2);
	glEnd();
	
	char message1[32];
	sprintf(message1,"Light: %d",Light);
	glColor3f(0.9, 0.9, 0.9);
	glRasterPos3f(Width/1.24, 30, 0.1);		 
	for (int i = 0; i < strlen(message1); i++) 
	{
	 	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,message1[i]);
	}
	
	char message[32];
	sprintf(message,"Shade Smooth: %d",ShadeSmooth);
	
	glRasterPos3f(Width/1.24, 50, 0.1);		 
	for (int i = 0; i < strlen(message); i++) 
	{
   	 	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,message[i]);
  	}
  	
  	char message2[32];
	sprintf(message2,"Shadows: %d",Shadows);
	glRasterPos3f(Width/1.24, 70, 0.1);		 
	for (int i = 0; i < strlen(message2); i++) 
	{
   	 	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,message2[i]);
  	}
	 	
  	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Grid()
{
	glPushMatrix();
		glLineWidth(1.0);
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_LINES);
			for(int i=-10;i<=10;i++) 
			{
			    glVertex3f(i,0,-10);
			    glVertex3f(i,0,10);
			    
			    glVertex3f(-10,0,i);
			    glVertex3f(10,0,i);
			}
		glEnd();
	glPopMatrix();
}

void Coord()
{
	glPushMatrix();
		glLineWidth(2.5);		
		glBegin(GL_LINES);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 10.0);
			glVertex3f(0.0, 0.0, -10.0);
			
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-10.0, 0.0, 0.0);
			glVertex3f(10.0, 0.0, 0.0);
			
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, -10.0, 0.0);
			glVertex3f(0.0, 10.0, 0.0);
		glEnd();	
	glPopMatrix();
}

float rotation = 0.0;

void LightPos()
{
	/**** Light ****/
	if(Light == true)
	{
		glPushMatrix();
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_COLOR_MATERIAL);	
			glColor3f(1.0, 1.0, 0.0);
			glTranslatef(LightPosX, LightPosY, LightPosZ);
			if(Start == false) glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_COLOR_MATERIAL);
	}
	
	
	rotation += 0.01;
	LightPosX = (8*cos(rotation));
	LightPosZ = (8*sin(rotation));
	
	GLfloat LightPosition[] ={LightPosX, LightPosY, LightPosZ, 0.0};
	GLfloat AmbientLight[] = {1.0, 1.0, 1.0};
	GLfloat DiffuseLight[] = {1.0, 1.0, 1.0}; 
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv (GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	
	if(Shadows == true)
	{
		Shadow();
	}
	if(Shadows == false)
	{
		glColor3f(1.0, 1.0, 1.0);
		
		MenuDrawP();
		glPushMatrix();
		glTranslatef(0.0, 1.0, 0.0);
			MenuDraw();	
			glEnable(GL_TEXTURE_2D);
		//	glBindTexture(GL_TEXTURE_2D, texture[0]);
				DrawOBJ();
			glDisable(GL_TEXTURE_2D);
			for(int i = 1; i <= STLC; i++)
			{
				render_blender(i);
			}
		glPopMatrix();
	}
}

void display()
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	
	StartCam = deltaStartCam;
	Poly = deltaPoly;
	
	if(Start == true)
	{
		/**** Game Mode ****/
		SCPX += deltaX * SCRX * 0.1;
		SCPY += deltaY * 0.1;
		SCPZ += deltaZ * SCRZ * 0.1;
	
		SCRX = cos(lx) * -cos(ly);
		SCRY = -sin(ly);
		SCRZ = sin(lx) * -cos(ly);
		
		gluLookAt(SCPX, SCPY, SCPZ,					//Cam Pos
				  SCPX+SCRX, SCPY+SCRY, SCPZ+SCRZ,	//Look At
				  0.0, 1.0, 0.0);					//Up
				  
	}
	if(Start == false)
	{		
		/**** Edit Mode ****/
		CPX = (cos(CRX) * -cos(CRY)) * zoom;
		CPY = (sin(CRY))* zoom;
		CPZ = (sin(CRX) * -cos(CRY)) * zoom;		  		
		
		gluLookAt(CPX, CPY, CPZ,
				  0.0, 0.0,  0.0,
				  0.0, 1.0,  0.0);	
					
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_COLOR_MATERIAL);
		
		/**** Draw Edit Mode Stuff like the Grid ****/
		Layout();
		Grid();
		Coord();
	}
	
	LightPos(); 
	
	if(ShadeSmooth == true) { glShadeModel (GL_SMOOTH);	}
	else { glShadeModel (GL_FLAT); }
	
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	
	if(Start == false)
	{
		if(key == 's')
		{
			PS = true;
			glutWarpPointer(Width/2, Height/2);
		}
	}
	
	if(Start == true)
	{
		float xrot, zrot; 
		xrot = (SCRX/180* 3.141592654f); 
		zrot = (SCRZ/180* 3.141592654f);
		
		if(key == 'w'){ deltaZ =  1.5; deltaX =  1.5; }
		if(key == 's'){ deltaZ =  -1.5; deltaX =  -1.5;}
		if(key == 'a'){ deltaX =  -1.5; deltaZ =  1.5;}
		if(key == 'd'){ deltaX = 1.5; deltaZ =  -1.5;}
		if(key == 32){ deltaY = 1.5; }	
	}
	
	if(key == '0' && StartCam == 0) { deltaStartCam = 1; Start = true;}	
	if(key == '0' && StartCam == 1) { deltaStartCam = 0; Start = false;}
	if(key == 27) {	exit(0); }
}
void KeyboardUP(unsigned char key, int x, int y)
{
	if(Start == false)
	{
		if(key == 's')
		{
			PS = false;
		}	
	}
	
	if(Start == true)
	{
		if(key == 'w'){ deltaZ = 0.0; deltaX = 0.0; deltaY = 0.0; }
		if(key == 's'){ deltaZ = 0.0; deltaX = 0.0; deltaY = 0.0; }
		if(key == 'a'){ deltaZ = 0.0; deltaX = 0.0; deltaY = 0.0; }
		if(key == 'd'){ deltaZ = 0.0; deltaX = 0.0; deltaY = 0.0; }
		if(key == 32){ deltaY = 0.0; }
	}

}

void Speckeys(int key, int x, int y)
{
	if(key == GLUT_KEY_F11) { glutFullScreenToggle(); }	
	if(key == GLUT_KEY_F5) { saveScreenshot("C://Screenshots//Screenshot.png"); }	
	if(key == GLUT_KEY_F3 && Poly == 0) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); deltaPoly = 1; }	
	if(key == GLUT_KEY_F3 && Poly == 1) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); deltaPoly = 0; }
}
	float lx1 = 0.0;
	float ly1 = 0.0;
void MouseMotion(int x, int y)
{
	if(Start == false)
	{
		if(MWP == true)
		{
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(Width/2, Height/2);
			
			lx1 += (x-Width/2);
			ly1 += (y-Height/2);
			
			CRX = (lx1 * 0.001);
			CRY = (ly1 * 0.001);
			
			if(ly1 < -1570.0)
			{
				CRY = -1.57;
				ly1 = -1570.0;
			}
			
			if(ly1 > 1570.0)
			{
				CRY = 1.57;
				ly1 = 1570.0;
			}		
		}
	}

}

float xx, yy = 0.0;
void MousePassiv(int x, int y)
{
	if(Start == false)
	{
		float lx, ly;
		
		lx = x - Width/2;
		
		if(PS == true)
		{
			glutSetCursor(GLUT_CURSOR_NONE);
			PlanS += (lx * 0.01);	
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
	
	if(Start == true)
	{
		glutWarpPointer(Width/2, Height/2);
		glutSetCursor(GLUT_CURSOR_NONE);
		
		xx += (x-Width/2);
		yy += (y-Height/2);
		
		lx = xx*0.001;
		ly = yy*0.001;
		
		
		if(ly < -1.5)
		{
			yy = -1500.0;
			ly = -1.5;
		}
		
		if(ly > 1.5)
		{
			yy = 1500.0;
			ly = 1.5;
		}	
	}
}

void MouseWheel(int button, int dir, int x, int y)
{		
	if(Start == false)
	{
		if (dir > 0)
	    {
			zoom -= 1.0;
	    }
	    else
	    {
			zoom += 1.0;
	    }	
	}
	
}

void Mouse(int button, int state, int x, int y)
{
	if(Start == false)
	{
		if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){ MWP = true;	}
		if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP){ MWP = false;	}	
	}
	if(Start == true)
	{
		
	}
	/*
	if(x <= Width && x >= Width/1.25 && y <= Height/2 && y >= 0.0)
	{
		printf("test\n");
	}
	*/
}


int main(int argc, char **argv)
{
	mkdir("C://Screenshots");
	printf("Press F11 for FullScreen\n");
	printf("Press F5 to make a Screenshot\n");
	printf("Press F3 for Polygon Line Mode\n");
	printf("Press 0 for Game/Edit Mode\n");
	printf("Screenshots will be saved under C:/Screenshots\n\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Unreal V_0.1");
	glutSetOption(GLUT_MULTISAMPLE, 4);
	
	glutDisplayFunc(display);	/**** Rendering ****/
	glutReshapeFunc(Resize);
	glutIdleFunc(display);
	
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));		/**** Print Devic Information ****/
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("OpenGL: %s\n\n", glGetString (GL_VERSION));
	
	glutKeyboardFunc(Keyboard);			/**** Button Inputs ****/
	glutKeyboardUpFunc(KeyboardUP);
	glutSpecialFunc(Speckeys);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiv);
	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	
	Menu();
	
	blender_file_data[0] = load_bin("Model//Monkey.stl", &blender_file_size[0]);
//	WriteSTL();
//	std::ifstream ifile("Handgun_Game_Cycles.obj");
//    model = LoadOBJ( ifile );
//	texture[0] = LoadTexture(MTL);
	
	glutMainLoop();
	return 0;
}

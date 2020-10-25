#ifndef _MENU_H_
#define _MENU_H_

const static float PlanVert[12]=
{
	-3.0, 0.0, -3.0,
	3.0, 0.0, -3.0,
	3.0, 0.0, 3.0,
	-3.0, 0.0, 3.0
};

const static float PlanNorm[12]=
{
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0
};

void MeshMenu(int value)
{
	switch(value)
	{
		case 1:
			PC += 1;
			break;
		case 2:
			CC += 1;
			break;
		case 3:
			SC += 1;
			break;
		case 4:
			COC += 1;
			break;
		case 5:
			TC += 1;
			break;
		case 6:
			MC += 1;
			break;
		case 7:
			CYC += 1;
			break;
	}
}

void LightMenu(int value)
{
	switch(value)
	{
		case 1:
			Light = true;
			break;
		case 2:
			Light = false;
			break;
		case 3:
			ShadeSmooth = true;
			break;
		case 4:
			ShadeSmooth = false;
			break;
		case 5:
			Shadows = true;
			break;
		case 6:
			Shadows = false;
			break;
		
	}
}

void LoadMenu(int value)
{
	switch(value)
	{
		case 1:
			OBJC += 1;
			open_OBJ(hwnd);
			break;
		case 2:
			STLC += 1;
			open_STL(hwnd);
			break;	
	}
}

void SaveMenu(int value)
{
	switch(value)
	{
		case 1:
			WriteSaves();
			break;
		case 2:
			LoadSaves();
			break;	
	}
}

void Menu()
{	
	int submenu = glutCreateMenu(MeshMenu);
	
	glutSetMenuFont(submenu, GLUT_BITMAP_HELVETICA_12);
		
	glutAddMenuEntry("Plane", 1);
	glutAddMenuEntry("Cube", 2);
	glutAddMenuEntry("Sphere", 3);
	glutAddMenuEntry("Cylinder", 7);
	glutAddMenuEntry("Cone", 4);
	glutAddMenuEntry("Torus", 5);
	glutAddMenuEntry("Monkey", 6);
	
	int submenu1 = glutCreateMenu(LightMenu);
	
	glutSetMenuFont(submenu1, GLUT_BITMAP_HELVETICA_12);
	
	glutAddMenuEntry("Light ON", 1);
	glutAddMenuEntry("Light OFF", 2);
	glutAddMenuEntry("Shade Smooth ON", 3);
	glutAddMenuEntry("Shade Smooth OFF", 4);
	glutAddMenuEntry("Shadows ON", 5);
	glutAddMenuEntry("Shadows OFF", 6);
	
	int submenu2 = glutCreateMenu(LoadMenu);
	
	glutSetMenuFont(submenu2, GLUT_BITMAP_HELVETICA_12);
	
	glutAddMenuEntry("Load OBJ", 1);
	glutAddMenuEntry("Load STL", 2);
	
	int submenu3 = glutCreateMenu(SaveMenu);
	
	glutSetMenuFont(submenu3, GLUT_BITMAP_HELVETICA_12);
	
	glutAddMenuEntry("Save Project", 1);
	glutAddMenuEntry("Load Project", 2);
	
	glutCreateMenu(LightMenu);
	glutAddSubMenu("Mesh", submenu);
	glutAddSubMenu("Light", submenu1);
	glutAddSubMenu("load Models", submenu2);
	glutAddSubMenu("Save/Load", submenu3);

	glutSetMenuFont(submenu2, GLUT_BITMAP_HELVETICA_12);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MenuDrawP()
{
	glColor3f(1.0, 1.0, 1.0);
	
	for(int i = 0; i < PC; i++)
	{
		glCullFace(GL_FRONT);
		glPushMatrix();
			glScalef(PlanS, 1.0, PlanS);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, PlanVert);
			glNormalPointer(GL_FLOAT, 4, PlanNorm);
			glDrawArrays(GL_QUADS, 0, 4);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		glPopMatrix();
		glCullFace(GL_BACK);
	}
}

void MenuDraw()
{	
//	glColor3f(1.0, 1.0, 1.0);

	for(int i = 0; i < CC; i++)
	{
		glPushMatrix();
			glutSolidCube(2.0);
		glPopMatrix();
	}
	
	for(int i = 0; i < SC; i++)
	{
		glPushMatrix();
			glutSolidSphere(1.0, 30, 30);
		glPopMatrix();
	}
	
	for(int i = 0; i < CYC; i++)
	{
		glPushMatrix();
			glutSolidCylinder(1.0, 3.0, 30, 30);
		glPopMatrix();
	}
	
	for(int i = 0; i < COC; i++)
	{
		glPushMatrix();
			glutSolidCone(1.0, 3.0, 30, 30);
		glPopMatrix();
	}
	
	for(int i = 0; i < TC; i++)
	{
		glPushMatrix();
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glutSolidTorus(0.5, 1.5, 30, 30);
		glPopMatrix();
	}
	
	for(int i = 0; i < MC; i++)
	{
		glPushMatrix();
			render_blender(0);
		glPopMatrix();
	}
	
}

#endif

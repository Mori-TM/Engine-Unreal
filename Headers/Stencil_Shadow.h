#ifndef _STENCIL_SHADOW_H_
#define _STENCIL_SHADOW_H_

float floorShadow[4][4];	// matrix used to calculate our projected floor shadow
float groundplane[]   = {0.0f, 1.0f, 0.0f, 1.0f}; // The normal of the floor
enum { X, Y, Z, W };

void MenuDrawP();
void MenuDraw();

void shadowmatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4])
{
	float dot = groundplane[X] * lightpos[X] + groundplane[Y] * lightpos[Y] + groundplane[Z] * lightpos[Z] + groundplane[W] * lightpos[W];

	shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
	shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
	shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
	shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

	shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
	shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
	shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
	shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

	shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
	shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
	shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
	shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

	shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
	shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
	shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
	shadowMat[3][3] = dot - lightpos[W] * groundplane[W];
}

void Shadow()
{	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glPushMatrix();
		//draw floor
		MenuDrawP();
	glPopMatrix();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glPushMatrix();
		// Draw the floor
		MenuDrawP();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 1.0, 0.0); //Shadow hight
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		float LightPosition[] = {LightPosX, LightPosY, LightPosZ, 0.0};
		shadowmatrix(floorShadow, groundplane, LightPosition);
		glMultMatrixf((float *)floorShadow);
		//Draw Shadow
		glTranslatef(0.0, 0.0, 0.0); //object height -1
		glColor4f(0.0, 0.0, 0.0, 0.7f);
			MenuDraw();
			DrawOBJ();
			for(int i = 1; i <= STLC; i++)
			{
				render_blender(i);
			}		
		glEnable(GL_DEPTH_TEST);
		if(Light == true) glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 1.0, 0.0);
		glDisable(GL_STENCIL_TEST);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		
		MenuDraw();
		glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, texture[0]);
			DrawOBJ();
		glDisable(GL_TEXTURE_2D);
	//	LoadWriteSTL();
		for(int i = 1; i <= STLC; i++)
		{
			render_blender(i);
		}
	glPopMatrix();
}

#endif

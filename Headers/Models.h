#ifndef _MODELS_H_
#define _MODELS_H_
#include <GL/freeglut.h>
void glutTexCube(double Size)
{
	glPushMatrix();
		glScalef(Size, Size, Size);
		
		glBegin(GL_QUADS);                
        //	glColor3f(1.0, 1.0, 1.0);
            glNormal3f( 0.0f, 1.0f, 0.0f);
            glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f,-1.0f);
            glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f,-1.0f);
            glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
            glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
	     glEnd();
	     // bottom
	     glBegin(GL_QUADS);
	    //  glColor3f(1.0, 1.0, 1.0);
            glNormal3f( 0.0f,-1.0f, 0.0f);                 
            glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);
            glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);
            glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
            glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);
	     glEnd();            
	     // left
	     glBegin(GL_QUADS);
	    //  glColor3f(1.0, 1.0, 1.0);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f,1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);
            glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);
            glTexCoord2f(1.0f,0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
	     glEnd();
	     // right
	     glBegin(GL_QUADS);
	    //  glColor3f(1.0, 1.0, 1.0);
            glNormal3f( 1.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);
            glTexCoord2f(0.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);
            glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);
	     glEnd();
	     // front
	     glBegin(GL_QUADS);
          //glColor3f(1.0, 1.0, 1.0);
            glNormal3f( 0.0f, 0.0f, 1.0f);
            glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);
            glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f,-1.0f, 1.0f);
	     glEnd();
	     // back
	     glBegin(GL_QUADS);
	    //  glColor3f(1.0, 1.0, 1.0);
            glNormal3f( 0.0f, 0.0f,-1.0f);
            glTexCoord2f(1.0f,1.0f); glVertex3f(-1.0f, 1.0f,-1.0f);
            glTexCoord2f(0.0f,1.0f); glVertex3f( 1.0f, 1.0f,-1.0f);
            glTexCoord2f(0.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);
            glTexCoord2f(1.0f,0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
	     glEnd();
	 glPopMatrix();	
}	


#endif

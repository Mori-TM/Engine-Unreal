#ifndef _TEXLOADER_H_
#define _TEXLOADER_H_
#include <GL/freeglut.h>
#include <stdio.h>
#include <images/stb_image.h>

GLuint texture[512];

int width = 0;
int height = 0;
int bitdepth = 0;

const int MinTexRes = 512;

GLuint LoadTex(const char *fn)
{
	unsigned char * data;
    
    stbi_set_flip_vertically_on_load(true);
	data = stbi_load(fn, &width, &height, &bitdepth, 0);
	
	printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    
	glGenTextures(1, &texture[512]);
	glBindTexture(GL_TEXTURE_2D, texture[512]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		/**** If Tex res is too low disable Mip-Mapping ****/
	if(width > MinTexRes && height > MinTexRes) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	if(width > MinTexRes && height > MinTexRes) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	if(width <= MinTexRes && height <= MinTexRes) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//No Tex Filtering
	if(width <= MinTexRes && height <= MinTexRes) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if(bitdepth == 3)gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data);
	if(bitdepth == 4)gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height,GL_RGBA, GL_UNSIGNED_BYTE, data);
//	glTexImage2D(GL_TEXTURE_2D, 0, bitdepth, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free( data );

	return texture[512];
}

#endif

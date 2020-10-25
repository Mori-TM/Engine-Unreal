#ifndef _STLLOADER_H_
#define _STLLOADER_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char *BlenderPath[512];

typedef unsigned char BYTE; // UINT8
typedef unsigned short int WORD; // UINT16

typedef struct blender_file_header_t 
{
	BYTE description[80];
	DWORD triangle_count;	
} BLENDER_FILE_HEADER;

typedef struct __attribute__((packed, aligned(1))) blender_triangle_t 
{
	float nv[3]; // x,y,z	
	float v1[3]; // x,y,z	
	float v2[3]; // x,y,z	
	float v3[3]; // x,y,z	
	WORD attr;	
} BLENDER_TRIANGLE;


int blender_file_count = 0;
void *blender_file_data[64] = { NULL };
size_t blender_file_size[64] = { 0 };

void* load_bin(char *path,size_t *size)
{
//	for(int i = 0; i <= blender_file_count; i++)
//	{
		blender_file_count ++;
		BlenderPath[blender_file_count] = path;	
//	}
	
	if (!path) return NULL;
	FILE *f = fopen(path,"rb");
	if (!f) return NULL;
	fseek(f,0,SEEK_END);
	size_t file_size = ftell(f);
	printf("size=%d\n",file_size);
	fseek(f,0,SEEK_SET);
	void *data = malloc(file_size);
	if (!data)
	{
		fclose(f);
	//	return NULL;
	}
	size_t bytes_readed = fread(data,sizeof(char),file_size,f);
	printf("bytes=%d\n",bytes_readed);	
	fclose(f);
	*size = file_size;
	
	
	printf("%d", blender_file_count);
	return data;
}

const static void render_blender(int id)
{
	BLENDER_FILE_HEADER *bfh = (BLENDER_FILE_HEADER*)blender_file_data[id];
	BLENDER_TRIANGLE *t = (BLENDER_TRIANGLE*)(bfh + 1);
	
	glPushMatrix();	
		glRotatef(270.0, 1.0, 0.0, 0.0);			
		glBegin(GL_TRIANGLES);		
		for (int i = 0; i < bfh->triangle_count; i++) 
		{
			glNormal3f(t->nv[0],t->nv[1],t->nv[2]);
		    glVertex3f(t->v1[0],t->v1[1],t->v1[2]);
			glVertex3f(t->v2[0],t->v2[1],t->v2[2]);
			glVertex3f(t->v3[0],t->v3[1],t->v3[2]);			    			    

			t++;
		}
		glEnd();
	glPopMatrix();
}

#endif

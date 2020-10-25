#ifndef _READ.WRITE_H_
#define _READ.WRITE_H_
#include <stdio.h>

#define FILE_NAME "Project1.cm"

char *Stlname[512];
int STLC1 = 0;

void LoadSaves()
{
	char path[128] = FILE_NAME;
	FILE *file = fopen("C://Screenshots//Project1.cm", "r");
	
	fscanf(file, "%f\n", &PlanS);
	fscanf(file, "%d\n", &PC);
	fscanf(file, "%d\n", &CC);
	fscanf(file, "%d\n", &SC);
	fscanf(file, "%d\n", &COC);
	fscanf(file, "%d\n", &TC);
	fscanf(file, "%d\n", &MC);
	fscanf(file, "%d\n", &CYC);
	fscanf(file, "%d\n", &STLC1);
	/*
//	fscanf(file, "%s\n", &STL_name);
	for(int i = 0; i <= STLC1; i++)
	{
	//	printf("%s\n", BlenderPath[0]);
	//	printf("%s\n", BlenderPath[1]);
		fscanf(file, "%s\n", &Stlname[i]);
		printf("%s\n", &Stlname[i]);
		blender_file_data[i] = load_bin(Stlname[i], &blender_file_size[i]);
	//	render_blender(0);	
	}
	*/
    fclose(file);
}

void WriteSaves()
{
	char path[128] = FILE_NAME;
	FILE* fp = fopen("C://Screenshots//Project1.cm", "w");
	
	fprintf(fp, "%f\n", PlanS);
	fprintf(fp, "%d\n", PC);
	fprintf(fp, "%d\n", CC);
	fprintf(fp, "%d\n", SC);
	fprintf(fp, "%d\n", COC);
	fprintf(fp, "%d\n", TC);
	fprintf(fp, "%d\n", MC);
	fprintf(fp, "%d\n", CYC);
	fprintf(fp, "%d\n", STLC);
	/*
	for(int i = 1; i <= blender_file_count; i++)
	{
		fprintf(fp, "%s\n", BlenderPath[i]);
	}
	*/
	
	fclose(fp);
}

#endif

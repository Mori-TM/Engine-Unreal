#ifndef _MTL_LOADER_H_
#define _MTL_LOADER_H_

char MTL[1024];
char USEMTL[1024];
char MTLNUM[1024];
int MTL_Count = 0;

char MTLNAME[3840];

float NS;
float KA[2];
float KD[3];
float KS[2];
float KE[2];
float D = 1.0;

void LoadMTL()
{
	FILE * file = fopen(MTLNAME, "r");
	if( file == NULL ){
	    printf("Impossible to open the file !\n");
	}
	
	while(1)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
    		break; 
        
        
        if ( strcmp( lineHeader, "newmtl" ) == 0 )
        {
			fscanf(file, "%s", &MTLNUM);
			printf("MTLNUM: %s\n", MTLNUM);
			MTL_Count += 1;
			printf("Mtl Count:%d\n", MTL_Count);
			
			if(strcmp( USEMTL, MTLNUM ) == 0)
			{
				
				printf("HELLLLLL");
			}
        }
        //Shiness
        if ( strcmp( lineHeader, "Ns" ) == 0 )
        {
			fscanf(file, "%f", &NS);
			printf("%f", NS);
        }
		//Ambient color
        if ( strcmp( lineHeader, "Ka" ) == 0 )
        {
			fscanf(file, "%f %f %f", &KA[0], &KA[1], &KA[2]);
			printf("%f", KA[0]);
			printf(" %f", KA[1]);
			printf(" %f\n", KA[2]);
        }
        //Diffuse color
        if ( strcmp( lineHeader, "Kd" ) == 0 )
        {
			fscanf(file, "%f %f %f", &KD[1], &KD[2], &KD[3]);
			printf("%f", KD[1]);
			printf(" %f", KD[2]);
			printf(" %f\n", KD[3]);
        }
        //Emissive color
        if ( strcmp( lineHeader, "Ks" ) == 0 )
        {
			fscanf(file, "%f %f %f", &KS[0], &KS[1], &KS[2]);
			printf("%f", KS[0]);
			printf(" %f", KS[1]);
			printf(" %f\n", KS[2]);
        }
        //Ambient color
        if ( strcmp( lineHeader, "Ke" ) == 0 )
        {
			fscanf(file, "%f %f %f", &KE[0], &KE[1], &KE[2]);
			printf("%f", KE[0]);
			printf(" %f", KE[1]);
			printf(" %f\n", KE[2]);
        }
        //Alpha color
        if ( strcmp( lineHeader, "d" ) == 0 )
        {
			fscanf(file, "%f", &D);
			printf("%f", D);
        }
        
        //Texture
        if ( strcmp( lineHeader, "map_Kd" ) == 0 )
        {
			fscanf(file, " %[^\n]s", &MTL);
			printf("MTLNAME: %s\n", MTLNAME);
			printf("%s\n", MTL);
        }
	}
	fclose(file);
}

#endif

#ifndef _FILE.DIALOG_H_
#define _FILE.DIALOG_H_ 

HWND hwnd;
char OBJ_name[1024] = "test";
char STL_name[1024] = "test";

int OBJC = 0;
int STLC = 0;

void open_OBJ(HWND hWnd)
{
	OPENFILENAME ofn;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = OBJ_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 1000;
	ofn.lpstrFilter = "OBJ Files\0*.obj*\0";
	ofn.nFilterIndex = 1;
	
	GetOpenFileName(&ofn);
	
	MTL_Count = 0;
	std::ifstream ifile(OBJ_name);
    model = LoadOBJ( ifile );
    texture[0] = LoadTex(MTL);
	
	printf("%s\n", OBJ_name);
}

void open_STL(HWND hWnd)
{
	OPENFILENAME ofn;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = STL_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 1000;
	ofn.lpstrFilter = "STL Files\0*.stl*\0";
	ofn.nFilterIndex = 1;
	
	GetOpenFileName(&ofn);
	
	blender_file_data[STLC] = load_bin(STL_name,&blender_file_size[STLC]);
	
	printf("%s\n", STL_name);
}

#endif

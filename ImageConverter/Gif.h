#pragma once

#include <string>

struct GifInfo
{
	unsigned char Format[3];
	unsigned char Version[3];
	unsigned char Width[2];
	unsigned char Height[2];
	unsigned char Global_Color_Table_Flag[1];
	unsigned char Color_Resolution[3];
	unsigned char Sort_Flag[1];
	unsigned char Size_of_Global_Color_Table[3];
	unsigned char Background_Color_Index[1];
	unsigned char Pixel_Aspect_Ratio[1];
};

void GifInit(std::string _fileName);
void SetGifFileName(std::string _fileName);
bool LoadGifInfo();

GifInfo GetGifInfo();
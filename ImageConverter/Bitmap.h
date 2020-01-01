#pragma once

#include <string>

struct BitmapInfo
{
	unsigned char Format[2];
	unsigned char Size[4];
	unsigned char HeaderSize[4];
	unsigned char InfoHeaderSize[4];
	unsigned char Width[4];
	unsigned char Height[4];
	unsigned char PlaneCount[2];
	unsigned char PixelCount[2];
	unsigned char CompressionFormat[2];
	unsigned char CompressionSize[2];
	unsigned char HorizontalCompression[4];
	unsigned char VerticalCompression[4];
	unsigned char ColorCount[4];
	unsigned char ImportantColorCountmp[4];
};

void BitmapInit(std::string _fileName);
void SetBitmapFileName(std::string _fileName);

bool LoadBitmapInfo();
BitmapInfo GetBitmapInfo();

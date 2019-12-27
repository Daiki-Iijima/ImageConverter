#include "Bitmap.h"

#include <string>
#include <fstream>		//	ファイルの入出力用

using namespace std;


Bitmap::BitmapInfo bitmapInfo;

string fileName;

Bitmap::Bitmap(std::string _fileName)
{
	fileName = _fileName;
}

void Bitmap::SetFileName(string _fileName)
{
	fileName = _fileName;
}

int Bitmap::HexCharToInt(char * _char)
{
	string hexStr(_char, sizeof(_char) / sizeof(_char[0]));	//	16進でサイズが入る

	char hexChar[100];

	sprintf_s(hexChar, "%x", hexStr);						//	16進のchar配列型に変換

	int octInt = std::stoi(hexChar, nullptr, 16);			// 16進を10進に変換してint型に代入

	return octInt;
}

void Bitmap::ChangeColor(string _outFileName, char _r, char _g, char _b, char _cr, char _cg, char _cb)
{
	ifstream ifs(fileName, ios::binary);                                           //	バイナリ形式で読み取り

	ofstream ofs(_outFileName.c_str(), ios::binary);		                        //	バイナリ形式で書き出し

	if (!ofs) {                                                                     //ターゲットファイルが開けなかったら終了
		return;
	}

	char temp;
	char rgb[4];

	//	ヘッダ部:54byte
	for (int i = 0; i < 54; i++)		                                            //	BITMAPFILEHEADER(ヘッダー情報)と、BITMAPINFOHEADER()をコピー
	{
		ifs.get(temp);
		ofs << temp;	                                                            //	アウトプットストリームにそのまま書き込む
	}

	int width = HexCharToInt((char*)bitmapInfo.Width);
	int height = HexCharToInt((char*)bitmapInfo.Height);

	int f = 0;
	int padding = (4 - width * (24 / 8) % 4) % 4;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3 + padding; j++)
		{
			ifs.get(temp);

			if (padding == 3)
			{
				if (j > width * 3 - padding + 2)
				{
					ofs << (char)0;
					continue;
				}
			}
			else
			{
				if (j > width * 3 - padding)
				{
					ofs << (char)0;
					continue;
				}
			}

			rgb[f] = temp;
			f++;

			if (f == 3) {
				f = 0;

				if (rgb[0] == _b && rgb[1] == _g && rgb[2] == _r) {                 //もし指定色なら
					rgb[0] = _cb;                                                   //B
					rgb[1] = _cg;                                                   //G
					rgb[2] = _cr;                                                   //R
				}
				ofs << rgb[0] << rgb[1] << rgb[2];
			}

		}

	}

}

bool Bitmap::GetBitmapInfo()
{
	ifstream ifs(fileName, ios::binary);										//	バイナリ形式で読み取り

	if (!ifs) return false; 													//	ターゲットファイルが開けなかったら終了

	char temp;																	//	キャッシュ用

	//	=== ヘッダ部:54byte ===
	for (int i = 0; i < 54; i++)	                                            //	BITMAPFILEHEADER(ヘッダー情報)と、BITMAPINFOHEADER()をコピー
	{
		ifs.get(temp);

		if (i >= 0 && i <= 1)		                                            //	フォーマットの種類
			bitmapInfo.Format[i] = temp;

		if (i >= 2 && i <= 5)		                                            //	2 - 5ビットはファイルサイズ(byte)
			bitmapInfo.Size[i - 2] = temp;

		if (i >= 10 && i <= 13)		                                            //	ヘッダサイズ
			bitmapInfo.HeaderSize[i - 10] = temp;

		if (i >= 14 && i <= 17)		                                            //	情報ヘッダサイズ
			bitmapInfo.InfoHeaderSize[i - 14] = temp;

		if (i >= 18 && i <= 21)		                                            //	画像の幅
			bitmapInfo.Width[i - 18] = temp;

		if (i >= 22 && i <= 25)		                                            //	画像の高さ
			bitmapInfo.Height[i - 22] = temp;

		if (i >= 26 && i <= 27)		                                            //	画像の高さ
			bitmapInfo.PlaneCount[i - 26] = temp;

		if (i >= 28 && i <= 29)		                                            //	画素数
			bitmapInfo.PixelCount[i - 28] = temp;

		if (i >= 30 && i <= 33)		                                            //	圧縮形式
			bitmapInfo.CompressionFormat[i - 30] = temp;

		if (i >= 34 && i <= 37)		                                            //	圧縮サイズ
			bitmapInfo.CompressionSize[i - 34] = temp;

		if (i >= 38 && i <= 41)		                                            //	水平解像度
			bitmapInfo.HorizontalCompression[i - 38] = temp;

		if (i >= 42 && i <= 45)		                                            //	垂直解像度
			bitmapInfo.VerticalCompression[i - 42] = temp;

		if (i >= 46 && i <= 49)		                                            //	色数
			bitmapInfo.ColorCount[i - 46] = temp;

		if (i >= 50 && i <= 53)		                                            //	重要色数
			bitmapInfo.ImportantColorCountmp[i - 50] = temp;
	}

	return true;
}
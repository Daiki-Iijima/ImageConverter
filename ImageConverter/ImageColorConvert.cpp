
#include "ImageColorConvert.h"

#include <string>
#include <fstream>		//	ファイルの入出力用

using namespace std;

int HexCharToInt(char * _char)
{
	string hexStr(_char, sizeof(_char) / sizeof(_char[0]));	//	16進でサイズが入る

	char hexChar[100];

	sprintf_s(hexChar, "%x", hexStr);						//	16進のchar配列型に変換

	int octInt = std::stoi(hexChar, nullptr, 16);			// 16進を10進に変換してint型に代入

	return octInt;
}

void ChangeColor(string _inputFileName,string _outFileName,int _width,int _height, char _r, char _g, char _b, char _cr, char _cg, char _cb)
{
	ifstream ifs(_inputFileName, ios::binary);                                           //	バイナリ形式で読み取り

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

	int width = _width;
	int height = _height;

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
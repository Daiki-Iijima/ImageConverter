#include <iostream>
#include <string>		//	文字列を扱う
#include <fstream>		//	ファイルの入出力用
#include <Windows.h>

#include "Bitmap.h"
using namespace std;

int width;
int height;

enum FILE_FORMAT
{
	NONE,
	BMP,
	PNG,
	GIF,
	JPEG,
};

FILE_FORMAT CheckFormat()
{
	FILE_FORMAT retFileFormat = NONE;


	return retFileFormat;
}

void TitleDraw()
{
	printf("                   ___                               ____                          _            \n"
		"                  |_ _|_ __ ___   __ _  __ _  ___   / ___|___  _ ____   _____ _ __| |_ ___ _ __ \n"
		"                   | || '_ ` _ \\ / _` |/ _` |/ _ \\ | |   / _ \\| '_ \\ \\ / / _ \\ '__| __/ _ \\ '__|\n"
		"                   | || | | | | | (_| | (_| |  __/ | |__| (_) | | | \\ V /  __/ |  | ||  __/ |   \n"
		"                  |___|_| |_| |_|\\__,_|\\__, |\\___|  \\____\\___/|_| |_|\\_/ \\___|_|   \\__\\___|_|   \n"
		"                                       |___/                                                    \n");

}

int HexCharToInt(char* _char)
{
	string hexStr(_char, sizeof(_char) / sizeof(_char[0]));	//	16進でサイズが入る

	char hexChar[100];

	sprintf_s(hexChar, "%x", hexStr);						//	16進のchar配列型に変換

	int octInt = std::stoi(hexChar, nullptr, 16);			// 16進を10進に変換してint型に代入

	return octInt;
}


void ChangeColor(string _filename, string _outFileName, char _r, char _g, char _b, char _cr, char _cg, char _cb)
{
	ifstream ifs(_filename, ios::binary);                                           //	バイナリ形式で読み取り

	ofstream ofs(_outFileName.c_str(), ios::binary);		                        //	バイナリ形式で書き出し

	if (!ofs) {                                                                     //ターゲットファイルが開けなかったら終了
		cout << "file open error" << endl;
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
char* GetDirectory(char* _outFilename)
{
	char cdir[255];
	GetCurrentDirectory(255, cdir);

	strcat_s(cdir, "\\");
	strcat_s(cdir, _outFilename);

	return cdir;
}

int main()
{

	TitleDraw();	                                                                //	タイトル画面
	cout << "ファイル名を入力してください" << endl;
	string _filename;
	cin >> _filename;

	Bitmap bitmap;

	bitmap.SetFileName(_filename);



	if (bitmap.GetBitmapInfo())                                                   //	画像情報
	{
		cout << "=== 読み取り成功 === " << endl;
		getchar();
	}
	else
	{
		cout << "読み取りに失敗しました" << endl;

		getchar();

		return 0;
	}

	cout << "出力する画像ファイル名を指定してください" << endl;

	string _outFilename;
	cin >> _outFilename;


	cout << GetDirectory((char*)_outFilename.c_str()) << endl;

	int targetColors[3];
	int changeColors[3];

	cout << "変更したい色を指定してください(例:(RGB)255 255 255)" << endl;

	cin >> targetColors[0] >> targetColors[1] >> targetColors[2];
	cin >> changeColors[0] >> changeColors[1] >> changeColors[2];

	ChangeColor(_filename, _outFilename,
		targetColors[0], targetColors[1], targetColors[2],		//	変更したい対象の色
		changeColors[0], changeColors[1], changeColors[2]);		//	変更後の色

	cout << "変更完了しました" << endl;

	ShellExecute(NULL, NULL, GetDirectory((char*)_outFilename.c_str()), NULL, NULL, SW_SHOW);
	getchar();
	getchar();
	return 0;
}
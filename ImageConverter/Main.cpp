#include <iostream>
#include <string>		//	文字列を扱う
#include <fstream>		//	ファイルの入出力用

#include <bitset>
using namespace std;

void TitleDraw()
{
	printf("                   ___                               ____                          _            \n"
		"                  |_ _|_ __ ___   __ _  __ _  ___   / ___|___  _ ____   _____ _ __| |_ ___ _ __ \n"
		"                   | || '_ ` _ \\ / _` |/ _` |/ _ \\ | |   / _ \\| '_ \\ \\ / / _ \\ '__| __/ _ \\ '__|\n"
		"                   | || | | | | | (_| | (_| |  __/ | |__| (_) | | | \\ V /  __/ |  | ||  __/ |   \n"
		"                  |___|_| |_| |_|\\__,_|\\__, |\\___|  \\____\\___/|_| |_|\\_/ \\___|_|   \\__\\___|_|   \n"
		"                                       |___/                                                    \n");

}


void loadFile()
{
	ifstream ifs("face.bmp", ios::binary);//	バイナリ形式で読み取り

	int i;
	char temp;
	char tempSize[4];
	char rgb[4];

	//	ヘッダ部:54byte
	for (i = 0; i < 54; i++)		//	BITMAPFILEHEADER(ヘッダー情報)と、BITMAPINFOHEADER()をコピー
	{
		ifs.get(temp);

		if (i >= 2 && i <= 5)	//	2 - 5ビットはファイルサイズ(byte)
		{
			tempSize[i - 2] = temp;
		}

	}

	unsigned char dat = tempSize[0] & 0xff;

	string size(tempSize, sizeof(tempSize) / sizeof(tempSize[0]));	//	16進でサイズが入る

	char    str[100];

	sprintf_s(str, "%x", size);

	int v = std::stoi(str, nullptr, 16); // 16進を10進に変換してint型に代入
	printf("Size:%d", v);
}

int main()
{
	loadFile();

	getchar();

	return 0;
}
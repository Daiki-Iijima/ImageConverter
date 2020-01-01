#include <iostream>
#include <string>		//	文字列を扱う
#include <fstream>		//	ファイルの入出力用
#include <Windows.h>

#include "ImageColorConvert.h"
#include "Bitmap.h"
#include "Gif.h"

using namespace std;

enum FILE_FORMAT
{
	NONE,
	BMP,
	GIF,
	PNG,
	JPEG,
};

FILE_FORMAT CheckFormat(string _filename)
{
	if (_filename.find(".bmp") != std::string::npos) { return BMP; }
	if (_filename.find(".gif") != std::string::npos) { return GIF; }
	if (_filename.find(".png") != std::string::npos) { return PNG; }
	if (_filename.find(".jpeg") != std::string::npos) { return JPEG; }

	return NONE;
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

	cout << "読み取るファイル名を入力してください" << endl;

	string _inputFilenNme;
	//cin >> _inputFilenNme;
	_inputFilenNme = "Images/16_16.gif";

	cout << "出力する画像ファイル名を指定してください" << endl;

	string _outFileName;
	//cin >> _outFileName;
	_outFileName = "t.gif";

	cout << GetDirectory((char*)_outFileName.c_str()) << endl;	//	出力するディレクトリを表示

	switch (CheckFormat(_inputFilenNme))
	{
	case BMP:
	{
		BitmapInit(_inputFilenNme);									//	ファイル名を設定する

		if (LoadBitmapInfo())										//	画像情報
		{
			cout << "=== 読み取り成功 === " << endl;
		}
		else
		{
			cout << "読み取りに失敗" << endl;
			return 0;
		}

		int targetColors[3];
		int changeColors[3];

		cout << "変更したい色を指定してください(例:(RGB)255 255 255)" << endl;

		cin >> targetColors[0] >> targetColors[1] >> targetColors[2];
		cin >> changeColors[0] >> changeColors[1] >> changeColors[2];

		ChangeColor(
			_inputFilenNme,											//	入力するファイル名
			_outFileName,											//	出力するファイル名
			HexCharToInt((char*)GetBitmapInfo().Width),				//	幅
			HexCharToInt((char*)GetBitmapInfo().Height),			//	高さ
			targetColors[0], targetColors[1], targetColors[2],		//	変更したい対象の色
			changeColors[0], changeColors[1], changeColors[2]);		//	変更後の色

	}
	break;
	case GIF:
	{
		GifInit(_inputFilenNme);

		if (LoadGifInfo())
		{
			cout << "=== 読み取り成功 ===" << endl;
		}
		else
		{
			cout << "読み取りに失敗" << endl;
			return 0;
		}

		GifInfo info = GetGifInfo();

		for (int i = 0; i < sizeof(info.Format); i++)
		{
			printf("F:%c", info.Format[i]);
		}
		printf("\n");

		for (int i = 0; i < sizeof(info.Version); i++)
		{
			printf("V:%c", info.Version[i]);
		}
		printf("\n");

		for (int i = 0; i < sizeof(info.Width); i++)
		{
			printf("W:%d", info.Width[i]);
		}
		printf("\n");

		for (int i = 0; i < sizeof(info.Height); i++)
		{
			printf("H:%d", info.Height[i]);
		}
		printf("\n");

		for (int i = 0; i < sizeof(info.Global_Color_Table_Flag); i++)
		{
			printf("G:%d", info.Global_Color_Table_Flag[i]);
		}
		printf("\n");

		for (int i = 0; i < sizeof(info.Color_Resolution); i++)
		{
			printf("C:%d", info.Color_Resolution[i]);
		}
		printf("\n");

		for (int i = 0; i < sizeof(info.Sort_Flag); i++)
		{
			printf("So:%d", info.Sort_Flag[i]);
		}
		printf("\n");
		for (int i = 0; i < sizeof(info.Size_of_Global_Color_Table); i++)
		{
			printf("S:%d", info.Size_of_Global_Color_Table[i]);
		}
		printf("\n");
		for (int i = 0; i < sizeof(info.Background_Color_Index); i++)
		{
			printf("B:%d", info.Background_Color_Index[i]);
		}
		printf("\n");
		for (int i = 0; i < sizeof(info.Pixel_Aspect_Ratio); i++)
		{
			printf("P:%d", info.Pixel_Aspect_Ratio[i]);
		}
		printf("\n");

		int targetColors[3];
		int changeColors[3];

		cout << "変更したい色を指定してください(例:(RGB)255 255 255)" << endl;

		cin >> targetColors[0] >> targetColors[1] >> targetColors[2];
		cin >> changeColors[0] >> changeColors[1] >> changeColors[2];

		//ChangeColor(
		//	_inputFilenNme,											//	入力するファイル名
		//	_outFileName,											//	出力するファイル名
		//	HexCharToInt((char*)GetGifInfo().Width),				//	幅
		//	HexCharToInt((char*)GetGifInfo().Height),				//	高さ
		//	targetColors[0], targetColors[1], targetColors[2],		//	変更したい対象の色
		//	changeColors[0], changeColors[1], changeColors[2]);		//	変更後の色

	}
	break;
	}

	cout << "変更完了しました" << endl;

	//	ファイルを開く
	ShellExecute(NULL, NULL, GetDirectory((char*)_outFileName.c_str()), NULL, NULL, SW_SHOW);

	return 0;
}
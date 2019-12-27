#include <iostream>
#include <string>		//	文字列を扱う
#include <fstream>		//	ファイルの入出力用
#include <Windows.h>

#include "Bitmap.h"
using namespace std;

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

	string _filename;
	cin >> _filename;

	if (_filename.find(".bmp") != std::string::npos) {
		cout << "bitmapです" << endl;
	}

	Bitmap bitmap(_filename);														//	ファイル名を設定する



	if (bitmap.GetBitmapInfo())														//	画像情報
	{
		cout << "=== 読み取り成功 === " << endl;
		getchar();
	}
	else
	{
		cout << "読み取りに失敗" << endl;
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

	bitmap.ChangeColor(
		_outFilename,											//	出力するファイル名
		targetColors[0], targetColors[1], targetColors[2],		//	変更したい対象の色
		changeColors[0], changeColors[1], changeColors[2]);		//	変更後の色

	cout << "変更完了しました" << endl;

	//	ファイルを開く
	ShellExecute(NULL, NULL, GetDirectory((char*)_outFilename.c_str()), NULL, NULL, SW_SHOW);


	return 0;
}
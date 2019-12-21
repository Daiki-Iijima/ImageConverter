#include <iostream>
#include <string>		//	文字列を扱う
#include <fstream>		//	ファイルの入出力用

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

int HexCharToInt(char* _char)
{
	string hexStr(_char, sizeof(_char) / sizeof(_char[0]));	//	16進でサイズが入る

	char hexChar[100];

	sprintf_s(hexChar, "%x", hexStr);						//	16進のchar配列型に変換

	int octInt = std::stoi(hexChar, nullptr, 16);			// 16進を10進に変換してint型に代入

	return octInt;
}

int width;
int height;

//	INFOHEADERの情報を表示
//	TODO : 取得できるようにするのもいいかも
bool LoadInfoData(string _filename)
{
	ifstream ifs(_filename, ios::binary);//	バイナリ形式で読み取り

	if (!ifs) return false;        //ターゲットファイルが開けなかったら終了

	cout << "=== 正常に読み取りました ===" << endl;

	char temp;
	char tempSize[4];
	char tempFormat[2];
	char tempHeaderSize[4];
	char tempInfoHeaderSize[4];
	unsigned char tempWidth[4];
	unsigned char tempHeight[4];
	unsigned char tempPlaneCount[2];
	unsigned char tempPixelCount[2];
	unsigned char tempCompressionFormat[2];
	unsigned char tempCompressionSize[2];
	unsigned char tempHorizontalCompression[4];
	unsigned char tempVerticalCompression[4];
	unsigned char tempColorCount[4];
	unsigned char tempImportantColorCountmp[4];

	//	ヘッダ部:54byte
	for (int i = 0; i < 54; i++)	//	BITMAPFILEHEADER(ヘッダー情報)と、BITMAPINFOHEADER()をコピー
	{
		ifs.get(temp);

		if (i >= 0 && i <= 1)		//	フォーマットの種類
			tempFormat[i] = temp;

		if (i >= 2 && i <= 5)		//	2 - 5ビットはファイルサイズ(byte)
			tempSize[i - 2] = temp;

		if (i >= 10 && i <= 13)		//	ヘッダサイズ
			tempHeaderSize[i - 10] = temp;

		if (i >= 14 && i <= 17)		//	情報ヘッダサイズ
			tempInfoHeaderSize[i - 14] = temp;

		if (i >= 18 && i <= 21)		//	画像の幅
			tempWidth[i - 18] = temp;

		if (i >= 22 && i <= 25)		//	画像の高さ
			tempHeight[i - 22] = temp;

		if (i >= 26 && i <= 27)		//	画像の高さ
			tempPlaneCount[i - 26] = temp;

		if (i >= 28 && i <= 29)		//	画素数
			tempPixelCount[i - 28] = temp;

		if (i >= 30 && i <= 33)		//	圧縮形式
			tempCompressionFormat[i - 30] = temp;

		if (i >= 34 && i <= 37)		//	圧縮サイズ
			tempCompressionSize[i - 34] = temp;

		if (i >= 38 && i <= 41)		//	水平解像度
			tempHorizontalCompression[i - 38] = temp;

		if (i >= 42 && i <= 45)		//	垂直解像度
			tempVerticalCompression[i - 42] = temp;

		if (i >= 46 && i <= 49)		//	色数
			tempColorCount[i - 46] = temp;

		if (i >= 50 && i <= 53)		//	重要色数
			tempImportantColorCountmp[i - 50] = temp;
	}

	printf("フォーマット : %c%c\n", tempFormat[0], tempFormat[1]);				    // ファイル形式

	int _width = HexCharToInt((char*)tempWidth);									// ファイル横サイズ
	width = _width;
	printf("幅 : %d\n", _width);

	int _height = HexCharToInt((char*)tempHeight);								    // ファイル縦サイズ
	height = _height;
	printf("高さ : %d\n", _height);

	int size = HexCharToInt(tempSize);											    // サイズの算出
	printf("ファイルサイズ : %d\n", size);

	printf("プレーン数 : %d\n", tempPlaneCount[0]);								    // プレーン数の算出

	printf("ピクセル深度 : %d\n", tempPixelCount[0]);							    // 画素数の算出

	printf("圧縮形式 : %d\n", tempCompressionFormat[0]);						    // 圧縮形式の算出

	int compressionSize = HexCharToInt((char*)tempCompressionSize);				    // 圧縮サイズの算出
	printf("圧縮サイズ : %d\n", compressionSize);

	int horizontalCompression = HexCharToInt((char*)tempHorizontalCompression);	    // 水平解像度の算出
	printf("水平解像度 : %d\n", horizontalCompression);

	int verticalCompression = HexCharToInt((char*)tempVerticalCompression);		    // 垂直解像度の算出
	printf("垂直解像度 : %d\n", verticalCompression);

	int colorCount = HexCharToInt((char*)tempColorCount);						    // カラーインデックス数の算出
	printf("カラーインデックス数 : %d\n", colorCount);

	int importantColorCountmp = HexCharToInt((char*)tempImportantColorCountmp);	    // 重要インデックス数
	printf("重要インデックス数 : %d\n", importantColorCountmp);

	return true;
}


void ChangeColor(string _filename, char _r, char _g, char _b, char _cr, char _cg, char _cb)
{
	ifstream ifs(_filename, ios::binary);                                           //	バイナリ形式で読み取り

	_filename.insert(_filename.size() - 4, "new");
	ofstream ofs(_filename.c_str(), ios::binary);		                            //	バイナリ形式で書き出し

	if (!ofs) {                                                                     //ターゲットファイルが開けなかったら終了
		cout << "file open error" << endl;
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

int main()
{
	TitleDraw();	                                                                //	タイトル画面
	cout << "ファイル名を入力してください" << endl;
	string _filename;
	cin >> _filename;

	if (LoadInfoData(_filename))                                                    //	画像情報
	{
		cout << "============================" << endl;
		getchar();
	}
	else
	{
		cout << "読み取りに失敗しました" << endl;

		getchar();
	}

	int targetColors[3];
	int changeColors[3];

	cout << "変更したい色を指定してください(例:(RGB)255 255 255)" << endl;

	cin >> targetColors[0] >> targetColors[1]>> targetColors[2];
	cin >> changeColors[0] >> changeColors[1] >> changeColors[2];

	ChangeColor(_filename, 
		targetColors[0], targetColors[1], targetColors[2],		//	変更したい対象の色
		changeColors[0], changeColors[1], changeColors[2]);		//	変更後の色

	getchar();

	return 0;
}
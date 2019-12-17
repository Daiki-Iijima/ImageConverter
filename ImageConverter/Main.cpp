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


void loadFile()
{
	string filename = "test.bmp";
	ifstream ifs(filename, ios::binary);//	バイナリ形式で読み取り

	filename.insert(filename.size() - 4, "new");
	ofstream ofs(filename.c_str(), ios::binary);		//	バイナリ形式で書き出し

	if (!ofs) {        //ターゲットファイルが開けなかったら終了
		cout << "file open error" << endl;
	}

	char temp;
	char tempSize[4];
	char tempFormat[2];
	char tempHeaderSize[4];
	char tempInfoHeaderSize[4];
	unsigned char tempWidth[4];
	unsigned char tempHeight[4];
	unsigned char tempPixelCount[2];
	unsigned char tempCompressionFormat[2];
	unsigned char tempCompressionSize[2];
	unsigned char tempHorizontalCompression[4];
	unsigned char tempVerticalCompression[4];
	unsigned char tempColorCount[4];
	unsigned char tempImportantColorCountmp[4];

	char rgb[4];

	//	ヘッダ部:54byte
	for (int i = 0; i < 54; i++)		//	BITMAPFILEHEADER(ヘッダー情報)と、BITMAPINFOHEADER()をコピー
	{
		ifs.get(temp);
		ofs << temp;	//	アウトプットストリームにそのまま書き込む
		if (i >= 0 && i <= 1)		//	フォーマットの種類
		{
			tempFormat[i] = temp;
		}

		if (i >= 2 && i <= 5)		//	2 - 5ビットはファイルサイズ(byte)
		{
			tempSize[i - 2] = temp;
		}

		if (i >= 10 && i <= 13)		//	ヘッダサイズ
		{
			tempHeaderSize[i - 10] = temp;
		}

		if (i >= 14 && i <= 17)		//	情報ヘッダサイズ
		{
			tempInfoHeaderSize[i - 14] = temp;
		}

		if (i >= 18 && i <= 21)		//	画像の幅
		{
			tempWidth[i - 18] = temp;
		}
		if (i >= 22 && i <= 25)		//	画像の高さ
		{
			tempHeight[i - 22] = temp;
		}
		//	26,27はプレーン数(1)

		if (i >= 28 && i <= 29)		//	画素数
		{
			tempPixelCount[i - 28] = temp;
		}

		if (i >= 30 && i <= 33)		//	圧縮形式
		{
			tempCompressionFormat[i - 30] = temp;
		}

		if (i >= 34 && i <= 37)		//	圧縮サイズ
		{
			tempCompressionSize[i - 34] = temp;
		}

		if (i >= 38 && i <= 41)		//	水平解像度
		{
			tempHorizontalCompression[i - 38] = temp;
		}

		if (i >= 42 && i <= 45)		//	垂直解像度
		{
			tempVerticalCompression[i - 42] = temp;
		}

		if (i >= 46 && i <= 49)		//	色数
		{
			tempColorCount[i - 46] = temp;
		}
		if (i >= 50 && i <= 53)		//	重要色数
		{
			tempImportantColorCountmp[i - 50] = temp;
		}

		
	}

	//	===	ファイル形式 ===
	printf("フォーマット:%c%c\n", tempFormat[0], tempFormat[1]);
	//	====================

	//	=== ファイル縦横サイズ ===

	string hexWidthStr((char*)tempWidth, sizeof(tempWidth) / sizeof(tempWidth[0]));
	string hexHeightStr((char*)tempHeight, sizeof(tempHeight) / sizeof(tempHeight[0]));

	char hexWidth[100];
	char hexHeight[100];

	sprintf_s(hexWidth, "%x", hexWidthStr);									//	16進のchar配列型に変換
	sprintf_s(hexHeight, "%x", hexHeightStr);									//	16進のchar配列型に変換

	int width = std::stoi(hexWidth, nullptr, 16);								// 16進を10進に変換してint型に代入
	int height = std::stoi(hexHeight, nullptr, 16);								// 16進を10進に変換してint型に代入

	printf("幅:%d\n", width);
	printf("高さ:%d\n", height);

	//	==========================

	//	===	サイズの算出 ===
	string hexSizeStr(tempSize, sizeof(tempSize) / sizeof(tempSize[0]));	//	16進でサイズが入る

	char hexSize[100];

	sprintf_s(hexSize, "%x", hexSizeStr);									//	16進のchar配列型に変換

	int size = std::stoi(hexSize, nullptr, 16);								// 16進を10進に変換してint型に代入

	printf("Size:%d\n", size);
	//	====================

	//	=== 画素数の算出 ===
	for (int i = 0; i < sizeof(tempPixelCount); i++)
	{
		printf("ピクセル深度 : %d\n", tempPixelCount[i]);
	}
	//	====================

	//	=== 圧縮形式の算出 ===
	for (int i = 0; i < sizeof(tempCompressionFormat); i++)
	{
		printf("圧縮形式 : %x\n", tempCompressionFormat[i]);
	}
	//	======================

	//	=== 圧縮サイズの算出 ===
	string hexCompressionSizeStr((char*)tempCompressionSize, sizeof(tempCompressionSize) / sizeof(tempCompressionSize[0]));	//	16進でサイズが入る

	char hexCompressionSize[100];

	sprintf_s(hexCompressionSize, "%x", hexSizeStr);									//	16進のchar配列型に変換

	int compressionSize = std::stoi(hexCompressionSize, nullptr, 16);								// 16進を10進に変換してint型に代入

	printf("圧縮サイズ : %d\n", compressionSize);
	//	======================

//	=== 水平解像度の算出 ===
	string hexHorizontalCompressionStr((char*)tempHorizontalCompression, sizeof(tempHorizontalCompression) / sizeof(tempHorizontalCompression[0]));	//	16進でサイズが入る

	char hexHorizontalCompression[100];

	sprintf_s(hexHorizontalCompression, "%x", hexHorizontalCompressionStr);									//	16進のchar配列型に変換

	int horizontalCompression = std::stoi(hexHorizontalCompression, nullptr, 16);								// 16進を10進に変換してint型に代入

	printf("水平解像度 : %d\n", horizontalCompression);
	//	======================

//	=== 垂直解像度の算出 ===
	string hexVerticalCompressionStr((char*)tempVerticalCompression, sizeof(tempVerticalCompression) / sizeof(tempVerticalCompression[0]));	//	16進でサイズが入る

	char hexVerticalCompression[100];

	sprintf_s(hexVerticalCompression, "%x", hexVerticalCompressionStr);									//	16進のchar配列型に変換

	int verticalCompression = std::stoi(hexVerticalCompression, nullptr, 16);								// 16進を10進に変換してint型に代入

	printf("垂直解像度 : %d\n", verticalCompression);
	//	======================
	
	
	int i = 0;
	while (ifs.get(temp)) {     //後はファイル終了まで繰り返し
		rgb[i] = temp;
		i++;
		if (i == 3) {
			i = 0;
			if (rgb[0] == -1 && rgb[1] == -1 && rgb[2] == -1) {//もし白(全部-1)なら
				rgb[0] = 192;    //B
				rgb[1] = 192;    //G
				rgb[2] = 192;    //R
			}
			ofs << rgb[0] << rgb[1] << rgb[2];
		}
	}
}


void ChangeColor()
{

	string filename = "test.bmp";

	ifstream ifs(filename, ios::binary);
	if (!ifs) {        //ソースファイルが開けなかったら終了
		cout << "file open error" << endl;
	}

	filename.insert(filename.size() - 4, "new");
	ofstream ofs(filename.c_str(), ios::binary);
	if (!ofs) {        //ターゲットファイルが開けなかったら終了
		cout << "file open error" << endl;
	}

	int i;
	char temp;
	char rgb[4];

	for (i = 0; i < 54; i++) {     //BITMAPFILEHEADERとBITMAPINFOHEADERを丸々コピー
		ifs.get(temp);
		ofs << temp;
	}
	i = 0;
	while (ifs.get(temp)) {     //後はファイル終了まで繰り返し
		rgb[i] = temp;
		i++;
		if (i == 3) {
			i = 0;
			if (rgb[0] == -1 && rgb[1] == -1 && rgb[2] == -1) {//もし白(全部-1)なら
				rgb[0] = 192;    //B
				rgb[1] = 192;    //G
				rgb[2] = 192;    //R
			}
			ofs << rgb[0] << rgb[1] << rgb[2];
		}
	}
}

int main()
{
	TitleDraw();	//	タイトル画面

	loadFile();		//	画像情報
	//ChangeColor();

	getchar();
	return 0;
}
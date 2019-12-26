#include "Bitmap.h"

#include <string>
#include <fstream>		//	ファイルの入出力用

using namespace std;


Bitmap::BitmapInfo bitmapInfo;

string fileName;

void Bitmap::SetFileName(string _fileName)
{
	fileName = _fileName;
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
#include "Gif.h"
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>		//	ファイルの入出力用
#include "BitFlag.h"

using namespace std;

GifInfo gifInfo;
std::string gifFileName;

vector<vector<unsigned int>> ColorTable(1000, vector<unsigned int>(3, 0));

void GifInit(std::string _fileName)
{
	gifFileName = _fileName;
}


void SetGifFileName(std::string _fileName)
{
	gifFileName = _fileName;
}

bool LoadGifInfo()
{
	ifstream ifs(gifFileName, ios::binary);										//	バイナリ形式で読み取り

	if (!ifs) return false; 													//	ターゲットファイルが開けなかったら終了

	char temp;																	//	キャッシュ用

   //	=== ヘッダ部:13byte ===
	for (int i = 0; i < 13; i++)	                                            //	HEADER
	{
		ifs.get(temp);

		if (i >= 0 && i <= 2)
			gifInfo.Format[i] = temp;

		if (i >= 3 && i <= 5)
			gifInfo.Version[i - 3] = temp;

		if (i >= 6 && i <= 7)
			gifInfo.Width[i - 6] = temp;

		if (i >= 8 && i <= 9)
			gifInfo.Height[i - 8] = temp;

		if (i >= 10 && i <= 10)
		{
			unsigned char flags = (int)temp & 0xff;

			if ((flags & BIT_FLAG1) != 0)
				gifInfo.Global_Color_Table_Flag[0] = 1;

			if ((flags & BIT_FLAG2) != 0)
				gifInfo.Color_Resolution[0] = 1;
			if ((flags & BIT_FLAG4) != 0)
				gifInfo.Color_Resolution[1] = 1;
			if ((flags & BIT_FLAG8) != 0)
				gifInfo.Color_Resolution[2] = 1;

			if ((flags & BIT_FLAG16) != 0)
				gifInfo.Sort_Flag[0] = 1;

			if ((flags & BIT_FLAG32) != 0)
				gifInfo.Size_of_Global_Color_Table += 1;
			if ((flags & BIT_FLAG64) != 0)
				gifInfo.Size_of_Global_Color_Table += 2;
			if ((flags & BIT_FLAG128) != 0)
				gifInfo.Size_of_Global_Color_Table += 4;
		}

		if (i >= 11)
			gifInfo.Background_Color_Index[i - 11];
		if (i >= 12)
			gifInfo.Pixel_Aspect_Ratio[i - 12];

	}

	//	グローバルテーブルの数は
	//	2の(0～7) + 1乗
	gifInfo.Size_of_Global_Color_Table += 1;
	gifInfo.Size_of_Global_Color_Table = pow(2, gifInfo.Size_of_Global_Color_Table);

	int count = 0;
	for (int i = 0; i < gifInfo.Size_of_Global_Color_Table; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//cout << ifs.tellg() << endl;
			ifs.get(temp);

			ColorTable[i][j] = temp & 0xff;
		}

		cout <<
			"番号 : " << i << ":\t" <<
			ColorTable[i][0] << "\t" <<
			ColorTable[i][1] << "\t" <<
			ColorTable[i][2] <<
			endl;
	}

	//	拡張ブロックがあるかチェック


	return true;
}

GifInfo GetGifInfo()
{
	return gifInfo;
}

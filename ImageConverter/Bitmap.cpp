#include "Bitmap.h"

#include <string>
#include <fstream>		//	�t�@�C���̓��o�͗p

using namespace std;


Bitmap::BitmapInfo bitmapInfo;

string fileName;

void Bitmap::SetFileName(string _fileName)
{
	fileName = _fileName;
}

bool Bitmap::GetBitmapInfo()
{
	ifstream ifs(fileName, ios::binary);										//	�o�C�i���`���œǂݎ��

	if (!ifs) return false; 													//	�^�[�Q�b�g�t�@�C�����J���Ȃ�������I��

	char temp;																	//	�L���b�V���p

	//	=== �w�b�_��:54byte ===
	for (int i = 0; i < 54; i++)	                                            //	BITMAPFILEHEADER(�w�b�_�[���)�ƁABITMAPINFOHEADER()���R�s�[
	{
		ifs.get(temp);

		if (i >= 0 && i <= 1)		                                            //	�t�H�[�}�b�g�̎��
			bitmapInfo.Format[i] = temp;

		if (i >= 2 && i <= 5)		                                            //	2 - 5�r�b�g�̓t�@�C���T�C�Y(byte)
			bitmapInfo.Size[i - 2] = temp;

		if (i >= 10 && i <= 13)		                                            //	�w�b�_�T�C�Y
			bitmapInfo.HeaderSize[i - 10] = temp;

		if (i >= 14 && i <= 17)		                                            //	���w�b�_�T�C�Y
			bitmapInfo.InfoHeaderSize[i - 14] = temp;

		if (i >= 18 && i <= 21)		                                            //	�摜�̕�
			bitmapInfo.Width[i - 18] = temp;

		if (i >= 22 && i <= 25)		                                            //	�摜�̍���
			bitmapInfo.Height[i - 22] = temp;

		if (i >= 26 && i <= 27)		                                            //	�摜�̍���
			bitmapInfo.PlaneCount[i - 26] = temp;

		if (i >= 28 && i <= 29)		                                            //	��f��
			bitmapInfo.PixelCount[i - 28] = temp;

		if (i >= 30 && i <= 33)		                                            //	���k�`��
			bitmapInfo.CompressionFormat[i - 30] = temp;

		if (i >= 34 && i <= 37)		                                            //	���k�T�C�Y
			bitmapInfo.CompressionSize[i - 34] = temp;

		if (i >= 38 && i <= 41)		                                            //	�����𑜓x
			bitmapInfo.HorizontalCompression[i - 38] = temp;

		if (i >= 42 && i <= 45)		                                            //	�����𑜓x
			bitmapInfo.VerticalCompression[i - 42] = temp;

		if (i >= 46 && i <= 49)		                                            //	�F��
			bitmapInfo.ColorCount[i - 46] = temp;

		if (i >= 50 && i <= 53)		                                            //	�d�v�F��
			bitmapInfo.ImportantColorCountmp[i - 50] = temp;
	}

	return true;
}
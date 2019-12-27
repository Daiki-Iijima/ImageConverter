#include "Bitmap.h"

#include <string>
#include <fstream>		//	�t�@�C���̓��o�͗p

using namespace std;


Bitmap::BitmapInfo bitmapInfo;

string fileName;

Bitmap::Bitmap(std::string _fileName)
{
	fileName = _fileName;
}

void Bitmap::SetFileName(string _fileName)
{
	fileName = _fileName;
}

int Bitmap::HexCharToInt(char * _char)
{
	string hexStr(_char, sizeof(_char) / sizeof(_char[0]));	//	16�i�ŃT�C�Y������

	char hexChar[100];

	sprintf_s(hexChar, "%x", hexStr);						//	16�i��char�z��^�ɕϊ�

	int octInt = std::stoi(hexChar, nullptr, 16);			// 16�i��10�i�ɕϊ�����int�^�ɑ��

	return octInt;
}

void Bitmap::ChangeColor(string _outFileName, char _r, char _g, char _b, char _cr, char _cg, char _cb)
{
	ifstream ifs(fileName, ios::binary);                                           //	�o�C�i���`���œǂݎ��

	ofstream ofs(_outFileName.c_str(), ios::binary);		                        //	�o�C�i���`���ŏ����o��

	if (!ofs) {                                                                     //�^�[�Q�b�g�t�@�C�����J���Ȃ�������I��
		return;
	}

	char temp;
	char rgb[4];

	//	�w�b�_��:54byte
	for (int i = 0; i < 54; i++)		                                            //	BITMAPFILEHEADER(�w�b�_�[���)�ƁABITMAPINFOHEADER()���R�s�[
	{
		ifs.get(temp);
		ofs << temp;	                                                            //	�A�E�g�v�b�g�X�g���[���ɂ��̂܂܏�������
	}

	int width = HexCharToInt((char*)bitmapInfo.Width);
	int height = HexCharToInt((char*)bitmapInfo.Height);

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

				if (rgb[0] == _b && rgb[1] == _g && rgb[2] == _r) {                 //�����w��F�Ȃ�
					rgb[0] = _cb;                                                   //B
					rgb[1] = _cg;                                                   //G
					rgb[2] = _cr;                                                   //R
				}
				ofs << rgb[0] << rgb[1] << rgb[2];
			}

		}

	}

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
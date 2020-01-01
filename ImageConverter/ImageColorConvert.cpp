
#include "ImageColorConvert.h"

#include <string>
#include <fstream>		//	�t�@�C���̓��o�͗p

using namespace std;

int HexCharToInt(char * _char)
{
	string hexStr(_char, sizeof(_char) / sizeof(_char[0]));	//	16�i�ŃT�C�Y������

	char hexChar[100];

	sprintf_s(hexChar, "%x", hexStr);						//	16�i��char�z��^�ɕϊ�

	int octInt = std::stoi(hexChar, nullptr, 16);			// 16�i��10�i�ɕϊ�����int�^�ɑ��

	return octInt;
}

void ChangeColor(string _inputFileName,string _outFileName,int _width,int _height, char _r, char _g, char _b, char _cr, char _cg, char _cb)
{
	ifstream ifs(_inputFileName, ios::binary);                                           //	�o�C�i���`���œǂݎ��

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

	int width = _width;
	int height = _height;

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
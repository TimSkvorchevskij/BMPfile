#include <iostream>
#include <fstream>
#include "BMPfile.h"

BMPfile::BMPfile(unsigned int weight, unsigned int height)
{
	bmpPtr = nullptr;
	std::fstream hex;
	hex.open("../Resource/template.bmp", std::ios_base::in | std::ios_base::binary);//файл с шаблоном заголовка
	if (!hex.is_open())
	{
		bmpPtr = nullptr;
		throw "error 3";
	}
	long long int rowSize = ((weight + 31) / 32) * 4;//формула из википедии, правильная
	long long int bodySize = rowSize * height;
	long long int fileSize = bodySize + 62;
	bmpPtr = new unsigned char[fileSize];
	for (size_t i = 0; i < 62; ++i)
	{
		hex.get((char&)(bmpPtr[i]));
	}
	hex.close();
	for (size_t i = 62; i < fileSize; ++i)
	{
		bmpPtr[i] = 0b11111111;//белый
	}

	//записываем параметры

	unsigned int tmp;

	bmpPtr[21] = weight & 0b11111111000000000000000000000000;
	tmp = weight & 0b00000000111111110000000000000000;
	bmpPtr[20] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = weight & 0b00000000000000001111111100000000;
	bmpPtr[19] = (tmp >> 1 * 8) & 0b00000000000000000000000011111111;
	bmpPtr[18] = weight & 0b00000000000000000000000011111111;;

	bmpPtr[25] = height & 0b11111111000000000000000000000000;
	tmp = height & 0b00000000111111110000000000000000;
	bmpPtr[24] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = height & 0b00000000000000001111111100000000;
	bmpPtr[23] = (tmp >> 1 * 8) & 0b00000000000000000000000011111111;
	bmpPtr[22] = height & 0b00000000000000000000000011111111;

	bmpPtr[5] = fileSize & 0b11111111000000000000000000000000;
	tmp = fileSize & 0b00000000111111110000000000000000;
	bmpPtr[4] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = fileSize & 0b00000000000000001111111100000000;
	bmpPtr[3] = (tmp >> 1 * 8) & 0b00000000000000000000000011111111;
	bmpPtr[2] = fileSize & 0b00000000000000000000000011111111;;

	bmpPtr[37] = bodySize & 0b11111111000000000000000000000000;
	tmp = bodySize & 0b00000000111111110000000000000000;
	bmpPtr[36] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = bodySize & 0b00000000000000001111111100000000;
	bmpPtr[35] = (tmp >> 8) & 0b00000000000000000000000011111111;
	bmpPtr[34] = bodySize & 0b00000000000000000000000011111111;
}

BMPfile::BMPfile(const char* namefile)//еще не проверено
{
	std::fstream file;
	file.open(namefile, std::ios_base::in | std::ios_base::binary);
	file.seekg(2, std::ios_base::beg);
	char fileSizeChar[4];
	file.read(fileSizeChar, 4);
	unsigned long long int fileSize = (fileSizeChar[3] << 3 * 8) | (fileSizeChar[2] << 2 * 8) | (fileSizeChar[1] << 8) | (fileSizeChar[0]);
	bmpPtr = new unsigned char[fileSize];
	file.seekg(0, std::ios_base::beg);
	file.read((char*)bmpPtr, fileSize);
}

BMPfile::~BMPfile()
{
	delete[] bmpPtr;
	bmpPtr = nullptr;
}

void BMPfile::write_bmp(const char* nameFile)
{
	if (bmpPtr == nullptr)
	{
		throw "error 4";
	}
	std::fstream file;
	file.open(nameFile, std::ios_base::out | std::ios_base::binary);
	if (!file.is_open())
	{
		delete[] bmpPtr;
		bmpPtr = nullptr;
		throw "Can't open file in write_bmp error 5";
	}
	//вытаскиваем размер всего файла
	unsigned long long int fileSize = (bmpPtr[5] << 3 * 8) | (bmpPtr[4] << 2 * 8) | (bmpPtr[3] << 8) | (bmpPtr[2]);
	file.write((char*)bmpPtr, fileSize);
	file.close();
}

void BMPfile::setPixel(unsigned int positionM, unsigned int positionN, unsigned char size) const //не готово
{
	int realPositionM = ((positionM + 31) / 32) * 4;
	int realPosition = realPositionM * positionN;
	if (size == 0)
	{
		bmpPtr[realPosition + 62] = 0b11111110;
	}
	else if (size == 1)
	{
		bmpPtr[realPosition + 62] = 0b11111111;
	}

}

unsigned int BMPfile::getWidth()const
{

}
unsigned int BMPfile::getHeight()const
{

}
bool BMPfile::getPixel(unsigned int positionM, unsigned int positionN) const
{

}
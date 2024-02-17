#include <iostream>
#include <fstream>

unsigned char* create_bmp(unsigned int weight, unsigned int height)
{
	std::fstream hex;
	hex.open("template.bmp", std::ios_base::in | std::ios_base::binary);//файл с шаблоном заголовка
	if (!hex.is_open())
	{
		std::cout << "error3" << std::endl;
		return nullptr;
	}
	long long int rowSize=((weight+31)/32)*4;//формула из википедии, правильная
	long long int bodySize = rowSize * height;
	long long int fileSize = bodySize  + 62;
	unsigned char* bmpPtr = new unsigned char[fileSize];
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

	return bmpPtr;
}

void write_bmp(const char* nameFile, unsigned char* bmp_ptr)
{
	if(bmp_ptr==nullptr)
	{
		std::cout<<"error 4"<<std::endl;
		return;
	}
	std::fstream file;
	file.open(nameFile, std::ios_base::out | std::ios_base::binary);
	if(!file.is_open())
	{
		std::cout<<"Can't open file in write_bmp error 5"<<std::endl;
		return;
	}
	//вытаскиваем размер всего файла
	unsigned long long int fileSize=(bmp_ptr[5]<<3*8)|(bmp_ptr[4]<<2*8)|(bmp_ptr[3]<<8)|(bmp_ptr[2]);
	file.write((char*)bmp_ptr, fileSize);
	file.close();
	delete[] bmp_ptr;
}

int main()
{
	write_bmp("Hi.bmp", create_bmp(40, 40));
    return 0;
}


#include <iostream>
#include <fstream>
//#define DEBUG
#define DEBUG2

unsigned char* create_bmp(unsigned int weight, unsigned int height)
{
	std::fstream hex;
	hex.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	if (!hex.is_open())
	{
		std::cout << "error3" << std::endl;
		return nullptr;
	}
	long long int rowSize=((weight+31)/32)*4;
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
		bmpPtr[i] = 0b00000000;
	}
	unsigned char tmp;

	bmpPtr[18] = (weight >> 3*8)|0b11111111;
	tmp = (weight << 8)|0b11111111;
	bmpPtr[19] = (tmp >> 3*8)|0b11111111;
	tmp = (weight << 2*8)|0b11111111;
	bmpPtr[20] = (tmp >> 3*8)|0b11111111;
	tmp = (weight << 3*8)|0b11111111;
	bmpPtr[21] = (tmp >> 3*8)|0b11111111;

	bmpPtr[22] = (height >> 3*8) | 0b11111111;
	tmp = (height << 8) | 0b11111111;
	bmpPtr[23] = (tmp >> 3*8) | 0b11111111;
	tmp = (height << 8*2) | 0b11111111;
	bmpPtr[24] = (tmp >> 3*8) | 0b11111111;
	tmp = (height << 8*3) | 0b11111111;
	bmpPtr[25] = (tmp >> 3*8) | 0b11111111;

	bmpPtr[2] = (fileSize >> 3*8) | 0b11111111;
	tmp = (fileSize << 8) | 0b11111111;
	bmpPtr[3] = (tmp >> 3*8) | 0b11111111;
	tmp = (fileSize << 8*2) | 0b11111111;
	bmpPtr[4] = (tmp >> 3*8) | 0b11111111;
	tmp = (fileSize << 3*8) | 0b11111111;
	bmpPtr[5] = (tmp >> 3*8) | 0b11111111;

	bmpPtr[34] = (bodySize >> 3*8) | 0b11111111;
	tmp = (bodySize << 8) | 0b11111111;
	bmpPtr[35] = (tmp >> 3*8) | 0b11111111;
	tmp = (bodySize << 8*2) | 0b11111111;
	bmpPtr[36] = (tmp >> 3*8) | 0b11111111;
	tmp = (bodySize << 3*8) | 0b11111111;
	bmpPtr[37] = (tmp >> 3*8) | 0b11111111;

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
	unsigned long long int fileSize=(bmp_ptr[2]<<3*8)|(bmp_ptr[3]<<2*8)|(bmp_ptr[4]<<8)|(bmp_ptr[5]);
#ifdef DEBUG2
	std::cout << "file size = " << fileSize << std::endl;
#endif // DEBUG2
	file.write((char*)bmp_ptr, fileSize);
	file.close();
	delete[] bmp_ptr;
}

int main()
{
	std::cout << "Hi. I'm working"<<std::endl;
#ifdef DEBUG
	std::fstream file1;
	file1.open("Number1_1152x648.bmp",std::ios_base::in|std::ios_base::binary);
	if (!file1.is_open())
	{
		std::cout << "file1 isn't open. error1" << std::endl;
		std::system("pause");
		return 1;
	}
	file1.seekg(10,std::ios_base::beg);
	int nomber1=0;
	file1.read((char*)(&nomber1), 4);
	std::cout << sizeof(nomber1) << std::endl;
	std::cout << nomber1 << std::endl;
	file1.seekg(0, std::ios_base::beg);
	char* hexFile = new char[nomber1];
	file1.read(hexFile, nomber1);
	file1.close();

	file1.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	file1.write(hexFile, nomber1);
	file1.close();

	delete[] hexFile;

	file1.open("Number1_1152x648.bmp", std::ios_base::in | std::ios_base::binary);
	int w;
	int h;
	file1.seekg(18, std::ios_base::beg);
	file1.read((char*)(&w), 4);
	file1.seekg(22, std::ios_base::beg);
	file1.read((char*)(&h), 4);
	std::cout << w << std::endl;//144
	std::cout << h << std::endl;//93312
	file1.seekg(34, std::ios_base::beg);
	int imageSize;
	file1.read((char*)(&imageSize), 4);
	std::cout << imageSize << std::endl;
	file1.close();

	file1.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	unsigned int n = 0;
	file1.seekp(2, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.seekp(18, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.seekp(22, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.seekp(34, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.close();

	//forBmp a;
	//std::cout << sizeof(a) << std::endl;
#endif // DEBUG
	write_bmp("Hi.bmp", create_bmp(40, 40));
	std::system("pause");
    return 0;
}


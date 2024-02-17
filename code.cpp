#include <iostream>
#include <fstream>
//#define DEBUG
//#define DEBUG2

unsigned char* create_bmp(unsigned int weight, unsigned int height)
{
	std::fstream hex;
	hex.open("template.bmp", std::ios_base::in | std::ios_base::binary);
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
		//hex.get(bmpPtr[i]);
	}                                         
	hex.close();
	for (size_t i = 62; i < fileSize; ++i)
	{
		bmpPtr[i] = 0b11111111;
	}

#ifdef DEBUG2
	std::cout << "rowsize = " << rowSize << std::endl;
	std::cout << "bodySize = " << bodySize << std::endl;
	std::cout << "fileSize = " << fileSize << std::endl;
	for (int i = 0; i < fileSize; ++i)
	{
		//std::cout << "bmpPtr[" << i << "] = |" << bmpPtr[i]<<std::endl;
	}
#endif // DEBUG2


	unsigned int tmp;

	bmpPtr[18] = weight & 0b11111111000000000000000000000000;         //(fileSize >> 3*8) & 0b11111111;
	tmp = weight & 0b00000000111111110000000000000000;
	bmpPtr[19] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = weight & 0b00000000000000001111111100000000;
	bmpPtr[20] = (tmp >> 1 * 8) & 0b00000000000000000000000011111111;
	bmpPtr[21] = weight & 0b00000000000000000000000011111111;;

	bmpPtr[22] = height & 0b11111111000000000000000000000000;         //(fileSize >> 3*8) & 0b11111111;
	tmp = height & 0b00000000111111110000000000000000;
	bmpPtr[23] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = height & 0b00000000000000001111111100000000;
	bmpPtr[24] = (tmp >> 1 * 8) & 0b00000000000000000000000011111111;
	bmpPtr[25] = height & 0b00000000000000000000000011111111;

	bmpPtr[2] = fileSize & 0b11111111000000000000000000000000;         //(fileSize >> 3*8) & 0b11111111;
	tmp = fileSize & 0b00000000111111110000000000000000;
	bmpPtr[3] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = fileSize & 0b00000000000000001111111100000000;
	bmpPtr[4] = (tmp >> 1 * 8) & 0b00000000000000000000000011111111;
	bmpPtr[5] = fileSize & 0b00000000000000000000000011111111;;

	bmpPtr[34] = bodySize & 0b11111111000000000000000000000000;         //(fileSize >> 3*8) & 0b11111111;
	tmp = bodySize & 0b00000000111111110000000000000000;
	bmpPtr[35] = (tmp >> 2 * 8) & 0b00000000000000000000000011111111;
	tmp = bodySize & 0b00000000000000001111111100000000;
	bmpPtr[36] = (tmp >> 8) & 0b00000000000000000000000011111111;
	bmpPtr[37] = bodySize & 0b00000000000000000000000011111111;

#ifdef DEBUG2
	std::cout << "bmpPtr[2] = " << static_cast<int>(bmpPtr[2]) << std::endl;
	std::cout << "bmpPtr[3] = " << static_cast<int>(bmpPtr[3]) << std::endl;
	std::cout << "bmpPtr[4] = " << static_cast<int>(bmpPtr[4]) << std::endl;
	std::cout << "bmpPtr[5] = " << static_cast<int>(bmpPtr[5]) << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "bmpPtr[18] = " << static_cast<int>(bmpPtr[18]) << std::endl;
	std::cout << "bmpPtr[19] = " << static_cast<int>(bmpPtr[19]) << std::endl;
	std::cout << "bmpPtr[20] = " << static_cast<int>(bmpPtr[20]) << std::endl;
	std::cout << "bmpPtr[21] = " << static_cast<int>(bmpPtr[21]) << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "bmpPtr[22] = " << static_cast<int>(bmpPtr[22]) << std::endl;
	std::cout << "bmpPtr[23] = " << static_cast<int>(bmpPtr[23]) << std::endl;
	std::cout << "bmpPtr[24] = " << static_cast<int>(bmpPtr[24]) << std::endl;
	std::cout << "bmpPtr[25] = " << static_cast<int>(bmpPtr[25]) << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "bmpPtr[34] = " << static_cast<int>(bmpPtr[34]) << std::endl;
	std::cout << "bmpPtr[35] = " << static_cast<int>(bmpPtr[35]) << std::endl;
	std::cout << "bmpPtr[36] = " << static_cast<int>(bmpPtr[36]) << std::endl;
	std::cout << "bmpPtr[37] = " << static_cast<int>(bmpPtr[37]) << std::endl;
	std::cout << "-------------------------" << std::endl;
#endif // DEBUG2


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
#ifdef DEBUG2
	std::cout << "Hi. I'm working" << std::endl;
#endif // DEBUG2
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
	char* hexFile = new char[62];
	file1.read(hexFile, 62);
	file1.close();

	std::cout << "start creane template" << std::endl;
	file1.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	file1.write(hexFile, nomber1);
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
	std::cout << "finish creane template" << std::endl;

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

	//file1.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	//
	//file1.close();

	//forBmp a;
	//std::cout << sizeof(a) << std::endl;
#endif // DEBUG
	write_bmp("Hi.bmp", create_bmp(40, 40));
#ifdef DEBUG2
	std::system("pause");
#endif // DEBUG2
    return 0;
}


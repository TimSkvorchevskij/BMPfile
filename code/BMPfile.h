#pragma once
#ifndef BMP_FILES_PVM
#define BMP_FILES_PVM

class BMPfile
{
	unsigned char* bmpPtr;
public:
	BMPfile(unsigned int weight = 40, unsigned int height = 40);
	BMPfile(const char* namefile);
	~BMPfile();
	void saveBmp(const char* nameFile);
	void setPixel(unsigned int positionM, unsigned int positionN, bool size) const;
	unsigned int getWidth()const;
	unsigned int getHeight()const;
	bool getPixel(unsigned int positionM, unsigned int positionN) const;
};

#endif
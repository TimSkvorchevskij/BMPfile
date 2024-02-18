#ifndef BMP_FILES_PVM
#define BMP_FILES_PVM

class BMPfile;
BMPfile::BMPfile(unsigned int weight, unsigned int height);
void BMPfile::write_bmp(const char* nameFile);
void BMPfile::changePixel(unsigned int positionM, unsigned int positionN, unsigned char size) const;

#endif
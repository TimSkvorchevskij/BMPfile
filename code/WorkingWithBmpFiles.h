#ifndef BMP_FILES_PVM
#define BMP_FILES_PVM

unsigned char* create_bmp(unsigned int weight, unsigned int height);
void write_bmp(const char* nameFile, unsigned char* bmp_ptr);

#endif
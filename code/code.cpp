#include "WorkingWithBmpFiles.h"

int main()
{
	unsigned char* bmp_ptr = create_bmp(9, 9);
	changePixel(bmp_ptr, 2, 2, 0);
	write_bmp("../Resource/Hi.bmp", bmp_ptr);
    return 0;
}


#include <iostream>
#include <fstream>
#include "BMPfile.h"

int main()
{
	try
	{
		BMPfile first(8, 8);
		first.saveBmp("../Resource/Hi.bmp");
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
		system("pause");
		return 1;
	}
    return 0;
}


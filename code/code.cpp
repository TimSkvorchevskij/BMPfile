#include <iostream>
#include <fstream>
#include "BMPfile.h"

int main()
{
	try
	{
		BMPfile first(40, 40);
		first.write_bmp("../Resource/Hi.bmp");
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
		system("pause");
		return 1;
	}
    return 0;
}


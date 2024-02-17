#include <iostream>
#include <fstream>

struct shiftHex
{
	unsigned long long int hex : 40;
};

int findLenForShift(const shiftHex& input)
{
	int count = 0;
	unsigned long long int hex = input.hex;
	do
	{
		++count;
		hex /= 0x10;
	} while (hex != 0x0);
	return count;
}

void printerShift(shiftHex& input)
{
	int len = findLenForShift(input);
	for (int i = 0; i < (10 - len); ++i)
	{
		std::cout << '0';
	}
	std::cout << std::hex << std::uppercase << input.hex;
}

long printerHexFile(const unsigned char* input, long lenInput)
{
	long count = 0;//Кол-во выводимых символов
	std::cout << std::hex << std::uppercase;
	for (long i = 0; i < lenInput; ++i)
	{
		count+=3;
		if (input[i] < 16)
		{
			std::cout << '0' << static_cast<int>(input[i]);
		}
		else
		{
			std::cout << static_cast<int>(input[i]);
		}
		std::cout << " ";
		if (i == 7)
		{
			std::cout << "| ";
			++count;
			++count;
		}
	}
	return count;
}

int main(int argc, char* argv[])
{
	if (argc > 6)
	{
		std::cout << "error1" << std::endl;
		return 0;
	}
	long n = -1;
	long s = 0;
	long all;
	std::fstream InFile;
	if (argc == 2)
	{
		InFile.open(argv[1], std::ios_base::in | std::ios_base::binary);
	}
	else if (argc == 4)
	{
		InFile.open(argv[3], std::ios_base::in | std::ios_base::binary);
		if (argv[1][1] == 'n')
		{
			n = atoi(argv[2]);
		}
		else if (argv[1][1] == 's')
		{
			s = atoi(argv[2]);
		}
		else
		{
			std::cout << "error2" << std::endl;
			return 0;
		}
	}
	else if (argc == 6)
	{
		InFile.open(argv[5], std::ios_base::in | std::ios_base::binary);
		if (argv[1][1] == 'n')
		{
			n = atoi(argv[2]);
			if (argv[3][1] == 's')
			{
				s = atoi(argv[4]);
			}
			else
			{
				std::cout << "error3" << std::endl;
				return 0;
			}
		}
		else if (argv[1][1] == 's')
		{
			s = atoi(argv[2]);
			if (argv[3][1] == 'n')
			{
				n = atoi(argv[4]);
			}
		}
		else
		{
			std::cout << "error4" << std::endl;
			return 0;
		}
	}
	else
	{
		std::cout << "error5" << std::endl;
		return 0;
	}
	if (!InFile.is_open())
	{
		std::cout << "Can't open file(error6)" << std::endl;
		return 0;
	}
	if (n == -1)
	{
		InFile.seekg(0, std::ios_base::end);
		n = InFile.tellg();
		InFile.seekg(0, std::ios_base::beg);
	}
	else
	{
		InFile.seekg(0, std::ios_base::end);
		all = InFile.tellg();
		InFile.seekg(0, std::ios_base::beg);
		if (n > all)
		{
			n = all;
		}
	}
	unsigned char buffer[16];
	shiftHex shift;
	shift.hex = 0x0;
	InFile.seekg(s, std::ios_base::beg);
	bool itsover = false;
	long count;//счетчик выведеных символов
	if ((n - s) < 16 and (n - s) > 0)//Debug19test
	{
		long lenBufferLast = (n - s);
		unsigned char* bufferLast = new unsigned char[lenBufferLast];
		InFile.read((char*)bufferLast, lenBufferLast);
		printerShift(shift);
		std::cout << ": ";
		count = printerHexFile(bufferLast, lenBufferLast);
		for (long i = count; i < 51; ++i)
		{
			if (i == 24)
			{
				std::cout << "|";
			}
			else
			{
				std::cout << " ";
			}
		}
		for (long i = 0; i < lenBufferLast; ++i)
		{
			if (bufferLast[i] >= 32)
			{
				std::cout << bufferLast[i];
			}
			else
			{
				std::cout << '.';
			}
		}
		delete[] bufferLast;
		itsover = true;
	}
	while (!itsover)
	{
		if ((n - InFile.tellg() + s) >= 16 and !InFile.eof())
		{
			InFile.read((char*)buffer, 16);
			printerShift(shift);
			shift.hex += 0x10;
			std::cout << ": ";
			printerHexFile(buffer, 16);//После останется пробел
			std::cout << " ";
			for (int i = 0; i < 16; ++i)
			{
				if (buffer[i] >= 32)
				{
					std::cout << buffer[i];
				}
				else
				{
					std::cout << '.';
				}
			}
			if ((n - InFile.tellg() + s) != 0)
			{
				std::cout << std::endl;
			}
		}
		else if ((n - InFile.tellg() + s) != 0 and !InFile.eof())
		{
			long lenBufferLast = (n - InFile.tellg() + s);
			unsigned char* bufferLast = new unsigned char[lenBufferLast];
			InFile.read((char*)bufferLast, lenBufferLast);
			printerShift(shift);
			std::cout << ": ";
			count = printerHexFile(bufferLast, lenBufferLast);
			for (long i = count; i < 51; ++i)
			{
				if (i == 24)
				{
					std::cout << "|";
				}
				else
				{
					std::cout << " ";
				}
			}
			for (long i = 0; i < lenBufferLast; ++i)
			{
				if (bufferLast[i] >= 32)
				{
					std::cout << bufferLast[i];
				}
				else
				{
					std::cout << '.';
				}
			}
			delete[] bufferLast;
			itsover = true;
		}
		else
		{
			itsover = true;
		}
	}
	InFile.close();
	return 0;
}

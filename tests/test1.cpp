#include <gtest/gtest.h>
#include "BMPfile.h"

TEST(BitMapTest, testSaveAndCreate)
{
	BMPfile first(40,40);
	first.saveBmp("My.bmp");
	ASSERT_EQ(0, std::system("fc My.bmp real.bmp"));
}

TEST(BitMapTest, testSetPixel)
{
	const size_t WIDTH = 40;
	const size_t HEIGHT = 40;
	
	BMPfile first(WIDTH,HEIGHT);
	for (size_t r = 0;r<3;++r)
		for (size_t c = 0;c < 3; ++c)
			first.setPixel(r,c,false);
	first.setPixel(1,1,true);

	for (size_t r = 0;r<3;++r)
		for (size_t c = 0;c < 3; ++c)
			first.setPixel(HEIGHT - r - 1,WIDTH - c - 1,false);
	first.setPixel(HEIGHT-2,WIDTH - 2,true);

	for (size_t r = 0;r<3;++r)
		for (size_t c = 0;c < 3; ++c)
			first.setPixel(r,WIDTH - c - 1,false);
	first.setPixel(1,WIDTH-2,true);

	first.saveBmp("MyQr.bmp");
	
	ASSERT_EQ(0, std::system("cmp MyQr.bmp Qr.bmp"));
}
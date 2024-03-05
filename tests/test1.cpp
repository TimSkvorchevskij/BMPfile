#include <gtest/gtest.h>
#include "BMPfile.h"

TEST(BitMapTest, testSaveAndCreate)
{
	BMPfile first(40,40);
	first.saveBmp("My.bmp");
	ASSERT_EQ(0, std::system("fc My.bmp real.bmp"));
}
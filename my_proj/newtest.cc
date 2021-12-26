#include <gtest/gtest.h>
#include "prac.h"



TEST(GarbageTest, BasicAssertions)
{
	EXPECT_EQ(5, 5);
	EXPECT_STRNE("TEST", "TRASH");
	//EXPECT_EQ(1, isgarbage());
}

TEST(MultTest, Assign)
{
	BigNumber BG(10);
	BigNumber GG(5);
	EXPECT_EQ(10, BG.number());
	EXPECT_EQ(5, GG.number());
}

TEST(MultTest, Mult)
{
	BigNumber BG(10);
	BigNumber GG(5);
	BG.multiply(BG, GG);
	EXPECT_EQ(50, GG.number());
}
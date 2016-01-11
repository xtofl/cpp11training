// cpp11training.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gtest/gtest.h>

int main(int argc, wchar_t** args)
{
	::testing::InitGoogleTest(&argc, args);
	return RUN_ALL_TESTS();
}


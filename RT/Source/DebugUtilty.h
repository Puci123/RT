#pragma once
#include <iostream>

namespace DebugU
{
	#define LOG_ERROR(X)	std::cout << "\033[1;31m[ERROR!]\033[0m\n\t" << X << std::endl
	#define ASSERT(X)		if(!(X)) __debugbreak()

	#define ASSERT_L(X,Y)		if(!(X)) LOG_ERROR(Y); \
							    if(!(X)) ASSERT(X)

}
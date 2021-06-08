
#include "test_core.hpp"

char Test_Success(void)
{
    std::cout << "*****SUCCESS*****" << std::endl;
     std::cout << "" << std::endl;
    return 0;
}

char Test_Error(void)
{
	std::cout << "*****ERROR*****" << std::endl;
    return 255;
}

void Test_Start(char const * text)
{
    std::cout << "*****START*****" << std::endl;
    std::cout << "Test name: " << text << std::endl;
}
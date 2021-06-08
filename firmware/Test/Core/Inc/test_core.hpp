#ifndef __TESTCORE_HPP__
#define __TESTCORE_HPP__

#include <iostream>

#define UT_SUCCESS return(Test_Success());
#define UT_ERROR return(Test_Error());
#define UT_START(x) Test_Start(x);

void Test_Start(char const *);
char Test_Success(void);
char Test_Error(void);

#endif /* __TESTCORE_HPP__ */
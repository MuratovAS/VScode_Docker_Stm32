/*  ISO C++.  */

#ifdef __cplusplus
#if !(defined(_BEGIN_STD_C) && defined(_END_STD_C))
#ifdef _HAVE_STD_CXX
#define _BEGIN_STD_C \
	namespace std    \
	{                \
		extern "C"   \
		{
#define _END_STD_C \
	}              \
	}
#else
#define _BEGIN_STD_C \
	extern "C"       \
	{
#define _END_STD_C }
#endif
//#if __GNUC_PREREQ(3, 3)
//#define _NOTHROW __attribute__((__nothrow__))
//#else
//#define _NOTHROW throw()
//#endif
#endif
#else
#define _BEGIN_STD_C
#define _END_STD_C
#define _NOTHROW
#endif

#ifndef COMMON_HEADER
#define COMMON_HEADER

#define TRUE 1
#define FALSE 0

//-----CHECK OS-----//
#ifdef __unix__ 

#elif defined(_WIN32) || defined(WIN32) 

#define OS_Windows

#endif
//-----CHECK OS-----//

#endif
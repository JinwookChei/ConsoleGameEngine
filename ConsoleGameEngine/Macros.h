#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif  // _DEBUG


#ifdef DEBUG
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK()
#endif
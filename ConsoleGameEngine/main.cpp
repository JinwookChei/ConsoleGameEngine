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


#include "ConsoleGameEngine.h"
#include <locale.h>


ConsoleGameEngine* GEngine = nullptr;

int main()
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//_CrtSetBreakAlloc(352);
#endif  // _DEBUG

    GEngine = new ConsoleGameEngine();
    if (nullptr == GEngine)
    {
        DEBUG_BREAK();
        return 0;
    }

    if (false == GEngine->Initialize())
    {
        DEBUG_BREAK();
        return 0;
    }

    GEngine->GameLoop();
    
    delete GEngine;
    GEngine = nullptr;

#ifdef _DEBUG
_ASSERT(_CrtCheckMemory());
#endif  // _DEBUG

return 0;

}
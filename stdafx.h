// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// Compile time hashing (Thanks to Xanvier)
template <unsigned int V>
static constexpr unsigned int compiler_stringhash_template = V;
static constexpr unsigned int compiler_stringhash(char const* str) {
    if (str == NULL) return 0;

    char* _str = ((char*)str);
    unsigned int result = -1;

    while (*_str != 0) {
        result = result * 0x21 + (unsigned int)(*_str);
        _str = _str + 1;
    }

    return result;
}

#define CT_bStringHash(s) compiler_stringhash_template<compiler_stringhash(s)>

// TODO: reference additional headers your program requires here

/*============================================================================
**
** Source: test1.c
**
** Purpose: Tests that CompareStringA returns the correct value and can handle
**          invalid parameters.
**
** 
**  Copyright (c) 2006 Microsoft Corporation.  All rights reserved.
** 
**  The use and distribution terms for this software are contained in the file
**  named license.txt, which can be found in the root of this distribution.
**  By using this software in any fashion, you are agreeing to be bound by the
**  terms of this license.
** 
**  You must not remove this notice, or any other, from this software.
** 
**
**==========================================================================*/

#define CSTR_LESS_THAN 1
#define CSTR_EQUAL 2
#define CSTR_GREATER_THAN 3

#include <palsuite.h>

int __cdecl main(int argc, char *argv[])
{    
    char str1[] = {'f','o','o',0};
    char str2[] = {'f','o','o','x',0};
    char str3[] = {'f','O','o',0};
    int flags = NORM_IGNORECASE | NORM_IGNOREWIDTH;
    int ret;

    if (0 != PAL_Initialize(argc, argv))
    {
        return FAIL;
    }

    ret = CompareStringA(0x0409, flags, str1, -1, str2, -1);
    if (ret != CSTR_LESS_THAN)
    {
        Fail("CompareStringA with \"%S\" (%d) and \"%S\" (%d) did not return "
            "CSTR_LESS_THAN!\n", str1, -1, str2, -1);
    }

    ret = CompareStringA(0x0409, flags, str1, -1, str2, 3);
    if (ret != CSTR_EQUAL)
    {
        Fail("CompareStringA with \"%S\" (%d) and \"%S\" (%d) did not return "
            "CSTR_EQUAL!\n", str1, -1, str2, 3);
    }

    ret = CompareStringA(0x0409, flags, str2, -1, str1, -1);
    if (ret != CSTR_GREATER_THAN)
    {
        Fail("CompareStringA with \"%S\" (%d) and \"%S\" (%d) did not return "
            "CSTR_GREATER_THAN!\n", str2, -1, str1, -1);
    }

    ret = CompareStringA(0x0409, flags, str1, -1, str3, -1);
    if (ret != CSTR_EQUAL)
    {
        Fail("CompareStringA with \"%S\" (%d) and \"%S\" (%d) did not return "
            "CSTR_EQUAL!\n", str1, -1, str3, -1);
    }

    ret = CompareStringA(0x0409, flags, str3, -1, str1, -1);
    if (ret != CSTR_EQUAL)
    {
        Fail("CompareStringA with \"%S\" (%d) and \"%S\" (%d) did not return "
            "CSTR_EQUAL!\n", str3, -1, str1, -1);
    }

    ret = CompareStringA(0x0409, flags, str3, -1, str1, -1);
    if (ret != CSTR_EQUAL)
    {
        Fail("CompareStringA with \"%S\" (%d) and \"%S\" (%d) did not return "
            "CSTR_EQUAL!\n", str3, -1, str1, -1);
    }

    ret = CompareStringA(0x0409, flags, str1, 0, str3, -1);
    if (ret != CSTR_LESS_THAN)
    {
        Fail("CompareStringA with \"%S\" (%d) and \"%S\" (%d) did not return "
            "CSTR_GREATER_THAN!\n", str1, 0, str3, -1);
    }

    
    ret = CompareStringA(0x0409, flags, NULL, -1, str3, -1);
    if (ret != 0)
    {
        Fail("CompareStringA should have returned 0, got %d!\n", ret);
    }
    if (GetLastError() != ERROR_INVALID_PARAMETER)
    {
        Fail("CompareStringA should have set the last error to "
            "ERROR_INVALID_PARAMETER!\n");
    }

    PAL_Terminate();

    return PASS;
}


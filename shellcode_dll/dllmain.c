#include <windows.h>

#include "ntdll.h"
#include "hash.h"
#include "win.h"

int EntryPoint()
{
	BYTE b_Dllname[] = { 'U', 'S', 'E', 'R', '3', '2', '.', 'D', 'L', 'L', 0 };
	BYTE b_coucou[] = { 'C', 'o', 'u', 'c', 'o', 'u', 0 };

	WIN32_MODULE	wModule = { 0 };
	WIN32_FUNCTION	wFunction = { 0 };

	wModule.KERNEL32 = fnGetModuleAddr(1822664912);
	if (wModule.KERNEL32 != NULL)
	{
		wFunction.fnLoadLibrary = fnGetProcAddr(wModule.KERNEL32, -2138098641);
		wModule.USER32 = wFunction.fnLoadLibrary(b_Dllname);

		if (wModule.USER32 != NULL)
		{
			wFunction.fnMessageBoxA = fnGetProcAddr(wModule.USER32, 1783602843);
			wFunction.fnMessageBoxA(NULL, b_coucou, b_coucou, MB_OK);
		}

	}

    return EXIT_SUCCESS;
}
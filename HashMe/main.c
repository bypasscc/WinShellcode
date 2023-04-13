#include <stdio.h>
#include <Windows.h>

#include "hash.h"

int main()
{
	WCHAR w_ModuleName[] = L"KERNEL32.DLL";
	BYTE b_FunctionName[] = "LoadLibraryA";

	INT32 moduleHash = HashStringMurmurW(w_ModuleName);
	INT32 functionHash = HashStringMurmurA(b_FunctionName);

	printf("%ws : %d\n%s : %d\n", w_ModuleName, moduleHash, b_FunctionName, functionHash);
}
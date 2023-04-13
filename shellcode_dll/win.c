#include "win.h"
#include "ntdll.h"

PVOID fnGetModuleAddr(INT32 ModuleHash) {
	PTEB pCurrentTeb = (PTEB)__readgsqword(0x30);
	PPEB pCurrentPeb = pCurrentTeb->ProcessEnvironmentBlock;
	PVOID pLdrDataEntryFirstEntry = (PVOID)((PBYTE)pCurrentPeb->Ldr->InMemoryOrderModuleList.Flink->Flink);

	LIST_ENTRY* pListParser = (DWORD64)pLdrDataEntryFirstEntry - 0x10;
	while (pListParser->Flink != pLdrDataEntryFirstEntry)
	{
		PLDR_DATA_TABLE_ENTRY pLdrDataEntry = pListParser;
		if (HashStringMurmurW(pLdrDataEntry->BaseDllName.Buffer) == ModuleHash)
		{
			return pLdrDataEntry->DllBase;
		}
		pListParser = pListParser->Flink;
	}
	return NULL;
}

PVOID fnGetProcAddr(PVOID pModuleAddr, INT32 FunctionHash)
{
	PIMAGE_DOS_HEADER pImageDosHeader = (PIMAGE_DOS_HEADER)pModuleAddr;
	PIMAGE_NT_HEADERS pImageNtHeaders = (PIMAGE_NT_HEADERS)((PBYTE)pModuleAddr + pImageDosHeader->e_lfanew);
	PIMAGE_EXPORT_DIRECTORY pImgExportDir = (PIMAGE_EXPORT_DIRECTORY)((PBYTE)pModuleAddr + pImageNtHeaders->OptionalHeader.DataDirectory[0].VirtualAddress);

	PDWORD pdwAddressOfFunctions = (PDWORD)((PBYTE)pModuleAddr + pImgExportDir->AddressOfFunctions);
	PDWORD pdwAddressOfNames = (PDWORD)((PBYTE)pModuleAddr + pImgExportDir->AddressOfNames);
	PWORD pwAddressOfNameOrdinales = (PWORD)((PBYTE)pModuleAddr + pImgExportDir->AddressOfNameOrdinals);

	for (WORD i = 0; i < pImgExportDir->NumberOfNames; i++)
	{
		PCHAR pczFunctionName = (PCHAR)((PBYTE)pModuleAddr + pdwAddressOfNames[i]);
		if (HashStringMurmurA(pczFunctionName) == FunctionHash)
		{
			return (PBYTE)pModuleAddr + pdwAddressOfFunctions[pwAddressOfNameOrdinales[i]];

		}
	}

	return NULL;
}
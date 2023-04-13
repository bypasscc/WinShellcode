#include <Windows.h>

typedef HMODULE(*pLoadLibrary)	(LPCSTR lpLibFileName);
typedef int		(*pMessageBoxA)	(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

typedef struct _WIN32_MODULE
{
	PVOID KERNEL32;
	PVOID USER32;

} WIN32_MODULE, * PWIN32_MODULE;

typedef struct _WIN32_FUNCTION
{
	pLoadLibrary fnLoadLibrary;
	pMessageBoxA fnMessageBoxA;

} WIN32_FUNCTION, * PWIN32_FUNCTION;

PVOID fnGetModuleAddr(INT32 ModuleHash);
PVOID fnGetProcAddr(PVOID pModuleAddr, INT32 FunctionHash);


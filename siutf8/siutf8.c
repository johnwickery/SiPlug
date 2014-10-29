/*
 * Check website http://blog.csdn.net/friendan/article/details/12226201
 * Check website http://blog.csdn.net/debugyt/article/details/8048666
 *
 * */
#include <windows.h>  
#include <stdio.h>
#include <conio.h>

#define FUNC_CREATEFFILE   0
#define FUNC_CLOSEHANDLE   1
#define FUNC_SETENDOFILE   2
#define FUNC_NUMBERS       (FUNC_SETENDOFILE+1)

struct SiHookStruct{
	BYTE oldEntry[5];
	BYTE newEntry[5];
	FARPROC oldFunc;
	FARPROC newFunc;
	BOOL hooked;
};

HANDLE moudle;
struct SiHookStruct siHook[FUNC_NUMBERS];

static void HookOn(FARPROC oFunction, BYTE *nEntry, BOOL *hooked);
static void HookOff(FARPROC oFunction, BYTE *oEntry, BOOL *hooked);


HANDLE WINAPI SiCreateFile(LPCTSTR lpFileName, DWORD dwDesiredAccess,
				DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	HANDLE ret;
	int i = FUNC_CREATEFFILE;

	HookOff(siHook[i].oldFunc, siHook[i].oldEntry, &(siHook[i].hooked));
	ret = (*siHook[i].oldFunc)(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, 
										dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	HookOn(siHook[i].oldFunc,  siHook[i].newEntry, &(siHook[i].hooked));
	return ret;
}

BOOL WINAPI SiCloseHandle(HANDLE hObject)
{
	BOOL ret;
	int i = FUNC_CLOSEHANDLE;

	HookOff(siHook[i].oldFunc, siHook[i].oldEntry, &(siHook[i].hooked));
	ret = (*siHook[i].oldFunc)(hObject);
	HookOn(siHook[i].oldFunc,  siHook[i].newEntry, &(siHook[i].hooked));
	return ret;
}

BOOL WINAPI SiSetEndOfFile(HANDLE hFile)
{
	BOOL ret;
	int i = FUNC_SETENDOFILE;

	HookOff(siHook[i].oldFunc, siHook[i].oldEntry, &(siHook[i].hooked));
	ret = (*siHook[i].oldFunc)(hFile);
	HookOn(siHook[i].oldFunc,  siHook[i].newEntry, &(siHook[i].hooked));
	return ret;
}


static void HookFunction(BYTE *oEntry, FARPROC oFunction, BYTE *nEntry, FARPROC nFunction)
{
	BYTE *nEntryplus;

/*
 * intel assembler diff from gas assembler
 * Check http://www.ibm.com/developerworks/cn/linux/l-gas-nasm.html
**/
#if 0
	/* this is intel assembler style*/
	/* Put real api address into oEntry */
	_asm
	{
		lea edi,oEntry
		mov esi,oFunction
		cld
		movsd
		movsb
	}
	/* 0xe9 equal jmp instruction */
	nEntry[0] = 0xe9;
	/* Get fake api relative address */
	_asm
	{
		lea eax,nFunction
		mov ebx,oFunction
		sub eax,ebx
		sub eax,5
		mov dword ptr [nEntry+1],eax
	}
#else
	/* this is gas assembler style*/
	/* Put real api address into oEntry */
	__asm__ __volatile__("leal %0, %%edi\n\t"
		"movl %1, %%esi\n\t"
		"cld\n\t"
		"movsd\n\t"
		"movsb\n\t"
		:
		:"m"(oEntry), "m"(oFunction));
	/* 0xe9 equal jmp instruction */
	nEntry[0] = 0xe9;
	nEntryplus = &nEntry[1];
	/* Get fake api relative address */
	__asm__ __volatile__("leal %1, %%eax\n\t"
		"movl %2, %%ebx\n\t"
		"subl %%ebx, %%eax\n\t"
		"subl $5,   %%eax\n\t"
		"movb %%al,  %0\n\t"
		:"=m"(nEntryplus)
		:"m"(nFunction), "m"(oFunction));
#endif
}

static void HookOn(FARPROC oFunction, BYTE *nEntry, BOOL *hooked)   
{
	DWORD dwTemp=0;
	DWORD dwOldProtect;
      
	VirtualProtectEx(INVALID_HANDLE_VALUE,  oFunction, 5, PAGE_READWRITE, &dwOldProtect);
	WriteProcessMemory(INVALID_HANDLE_VALUE,oFunction, nEntry, 5, 0);
	VirtualProtectEx(INVALID_HANDLE_VALUE,  oFunction, 5, dwOldProtect, &dwTemp);

	*hooked = TRUE;
}  

static void HookOff(FARPROC oFunction, BYTE *oEntry, BOOL *hooked)
{
	DWORD dwTemp=0;
	DWORD dwOldProtect;

	VirtualProtectEx(INVALID_HANDLE_VALUE,   oFunction, 5, PAGE_READWRITE, &dwOldProtect);
	WriteProcessMemory(INVALID_HANDLE_VALUE, oFunction, oEntry, 5, 0);
	VirtualProtectEx(INVALID_HANDLE_VALUE,   oFunction, 5, dwOldProtect, &dwTemp);

	*hooked = FALSE;   
}

static void Hook()  
{
	int i;

	memset(siHook, 0, sizeof(siHook));
	moudle = GetModuleHandle("kernel32.dll");

	/* Win32 Function values */
    siHook[FUNC_CREATEFFILE].oldFunc = (FARPROC)GetProcAddress(moudle, "CreateFile");
    siHook[FUNC_CLOSEHANDLE].oldFunc = (FARPROC)GetProcAddress(moudle, "CloseHandle");
    siHook[FUNC_SETENDOFILE].oldFunc = (FARPROC)GetProcAddress(moudle, "SetEndOfFile");

	/* Fake Function values */
    siHook[FUNC_CREATEFFILE].newFunc = (FARPROC)SiCreateFile;
    siHook[FUNC_CLOSEHANDLE].newFunc = (FARPROC)SiCloseHandle;
    siHook[FUNC_SETENDOFILE].newFunc = (FARPROC)SiSetEndOfFile;

	/* Feed siHook */
	for (i=FUNC_CREATEFFILE; i<FUNC_NUMBERS; i++) {
		HookFunction(siHook[i].oldEntry, siHook[i].oldFunc, siHook[i].newEntry, siHook[i].newFunc);
		HookOn(siHook[i].oldFunc, siHook[i].newEntry, &(siHook[i].hooked));
	}
}  
  
static void UnHook()  
{
	int i;

	/* Unfeed siHook */
	for (i=FUNC_CREATEFFILE; i<FUNC_NUMBERS; i++) {
		HookOff(siHook[i].oldFunc, siHook[i].oldEntry, &(siHook[i].hooked));
	}
	memset(siHook, 0, sizeof(siHook));
}  

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONOUT$","w",stdout);
        Hook();
        break;
    case DLL_PROCESS_DETACH:
        UnHook();
		FreeConsole();
        break;
    }
    return TRUE;
}


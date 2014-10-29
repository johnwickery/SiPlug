#include <windows.h>

static HMODULE m_hModule = NULL;	/* Original module handle */
static DWORD m_dwReturn[5] = {0};	/* Original function address */

static inline BOOL WINAPI Load()
{
    TCHAR tzPath[MAX_PATH];
    TCHAR tzTemp[MAX_PATH * 2];

    GetSystemDirectory(tzPath, MAX_PATH);
    lstrcat(tzPath, TEXT("\\msimg32"));
    m_hModule = LoadLibrary(tzPath);
    if (m_hModule == NULL)
    {
        wsprintf(tzTemp, TEXT("Can't Load %s"), tzPath);
        OutputDebugString(tzTemp);
        ExitProcess(-2);
    }
    else OutputDebugString("Loading msimg32");
    return (m_hModule != NULL);
}

static inline VOID WINAPI Free()
{
    if (m_hModule)
    {
        FreeLibrary(m_hModule);
    }
}

static FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
    FARPROC fpAddress;
    CHAR szProcName[16];
    TCHAR tzTemp[MAX_PATH];

    fpAddress = GetProcAddress(m_hModule, pszProcName);
    if (fpAddress == NULL)
    {
        if (HIWORD(pszProcName) == 0)
        {
            wsprintfA(szProcName, "%d", pszProcName);
            pszProcName = szProcName;
        }

        wsprintf(tzTemp, TEXT("Can't Find Function %s"), pszProcName);
        OutputDebugString(tzTemp);
        ExitProcess(-2);
    }

    return fpAddress;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        Load();

        HMODULE hMyDLL = LoadLibrary("sihook.dll");
        if (hMyDLL == NULL)
            OutputDebugString("Load sihook.dll failed");
        else
            OutputDebugString("Load sihook.dll success");
        return TRUE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        Free();
    }
    return TRUE;
}

typedef void (__cdecl *RemoteFunc)(void);

void __cdecl vSetDdrawflag(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("vSetDdrawflag");
    func();
}
void __cdecl AlphaBlend(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("AlphaBlend");
    func();
}
void __cdecl DllInitialize(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("DllInitialize");
    func();
}
void __cdecl GradientFill(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("GradientFill");
    func();
}
void __cdecl TransparentBlt(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("TransparentBlt");
    func();
}

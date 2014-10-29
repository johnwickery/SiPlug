#ifndef __UTILS__H__
#define __UTILS__H__

#include <windows.h>

#define SI_LOG_FILE       "silog.txt"

/* Output debug infomation */
void WINAPI OutputDebugStringEx(LPCTSTR lpcFormatText, ...);

/* Get short title */
char* GetSiSwTitle(const char* lpc,char* title);

/* Get file type */
/* 
 * 0 - None
 * 1 - .c    .cpp   .cxx  .cs
 * 2 - .h    .hpp   .hxx  .inc
 * 3 - .txt  .text  .doc
 * 4 - .php  .php3  .htm  .js
 * 5 - .pas  .vb    .pb   .vbs
**/
int GetColorIndex(const char* filename);

/* Easy log */
void SiLog(const char *fmt, ...);

#endif

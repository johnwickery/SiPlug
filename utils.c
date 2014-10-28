#include <stdio.h>
#include <string.h>
#include "utils.h"

void WINAPI OutputDebugStringEx(LPCTSTR lpcFormatText, ...)
{
	char szBuffer[1024];

    va_list argptr;
    va_start(argptr, lpcFormatText);
    wvsprintf(szBuffer, lpcFormatText, argptr);
    va_end(argptr);

	OutputDebugString(szBuffer);
}

char* GetSiSwTitle(const char* lpc,char* title)
{
	int i,len;
	int skip_flag;
	int index;
	skip_flag=0;
	i = index = 0;
	len = strlen(lpc);

	while(i<len)
	{
		if(lpc[i] == '(')
		{
			skip_flag = 1;
		}
		else if(lpc[i] == ')')
		{
			skip_flag = 0;
			i++;
			continue;
		}
		
		if(skip_flag == 0)
		{
			title[index++] = lpc[i];
		}
		
		i++;
	}
	title[index] = '\0';
	return title;
}

static const char* strstri(const char* str,const char* subStr)
{
    int len = strlen(subStr);
    if(len == 0)
    {
        return NULL;
    }

    while(*str)
    {
        if(strncasecmp(str, subStr, len) == 0)
        {
            return str;
        }
        ++str;
    }
    return NULL;
}

/* Get file type */
/* 
 * 0 - None
 * 1 - .c    .cpp   .cxx  .cs
 * 2 - .h    .hpp   .hxx  .inc
 * 3 - .txt  .text  .doc
 * 4 - .php  .php3  .htm  .js
 * 5 - .pas  .vb    .pb   .vbs
**/
int GetColorIndex(const char* filename)
{
	const char *p = NULL;
	/* type 1 */
	p = strstri(filename,".c");
	if(p != NULL)
		return 1;
	p = strstri(filename,".cpp");
	if(p != NULL)
		return 1;
	p = strstri(filename,".cxx");
	if(p != NULL)
		return 1;
	p = strstri(filename,".cs");
	if(p != NULL)
		return 1;
	/* type 2 */
	p = strstri(filename,".h");
	if(p != NULL)
		return 2;
	p = strstri(filename,".hpp");
	if(p != NULL)
		return 2;	
	p = strstri(filename,".hxx");
	if(p != NULL)
		return 2;	
	p = strstri(filename,".inc");
	if(p != NULL)
		return 2;
	/* type 3 */
	p = strstri(filename,".txt");
	if(p != NULL)
		return 3;
	p = strstri(filename,".text");
	if(p != NULL)
		return 3;	
	p = strstri(filename,".doc");
	if(p != NULL)
		return 3;	
	/* type 4 */
	p = strstri(filename,".php");
	if(p != NULL)
		return 4;
	p = strstri(filename,".php3");
	if(p != NULL)
		return 4;	
	p = strstri(filename,".htm");
	if(p != NULL)
		return 4;	
	p = strstri(filename,".js");
	if(p != NULL)
		return 4;
	/* type 5 */
	p = strstri(filename,".pas");
	if(p != NULL)
		return 5;
	p = strstri(filename,".pb");
	if(p != NULL)
		return 5;	
	p = strstri(filename,".vbs");
	if(p != NULL)
		return 5;	
	p = strstri(filename,".vb");
	if(p != NULL)
		return 5;		
									
	return 0;
}

void SiLog(const char *fmt, ...)
{
	char str[64] = {0};
	FILE *fp;
	va_list args;

	va_start(args, fmt);
	fp = fopen(SI_LOG_FILE,"at");
	vsprintf(str, fmt, args);
	fwrite(str, strlen(str), 1, fp);
	va_end(args);

	fclose(fp);
}

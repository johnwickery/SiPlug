#ifndef __SICHAR__H__
#define __SICHAR__H__

#if 0
#define CHARSET_ANSI      0
#define CHARSET_UTF8      1
#define CHARSET_UNICODE   2
#else
typedef enum{
	CHARSET_ERR = -1,
	CHARSET_ANSI,
	CHARSET_UTF8,
	CHARSET_UNICODE,
	CHARSET_UNICODE_BIGEND,
	CHARSET_NUMBER
}SI_CHARSET;
#endif

#endif /* __SICHAR__H__ */

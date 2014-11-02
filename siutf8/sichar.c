#include "sichar.h"

SI_CHARSET GetCharSetType(char *buf)
{
	SI_CHARSET charset;

	if (buf[0] == '\0') {
		return CHARSET_ERR;
	}
#if 0
	if(buf[0] == 0xef && buf[1] == 0xbb && buf[2] == 0xbf) {
		/* UTF-8 */
		charset = CHARSET_UTF8;
	} else if (buf[0] == 0xff && buf[1] == 0xfe) {
		/* Unicode */
		charset = CHARSET_UNICODE;
	} else if (buf[0] == 0xfe && buf[1] == 0xff) {
		/* Unicode Bigendian */
		charset = CHARSET_UNICODE_BIGEND;
	} else {
		/* Support other to be ANSI */
		charset = CHARSET_ANSI;
	}
#endif
	return charset;
}


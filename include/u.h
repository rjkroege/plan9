#ifndef _U_H_
#define _U_H_ 1
#if defined(__cplusplus)
extern "C" {
#endif

#define __BSD_VISIBLE 1 /* FreeBSD 5.x */
#define __EXTENSIONS__ 1 /* SunOS */
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1
#define _XOPEN_SOURCE 1000
#define _XOPEN_SOURCE_EXTENDED 1
#define _LARGEFILE64_SOURCE 1
#define _FILE_OFFSET_BITS 64

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <assert.h>
#include <setjmp.h>
#include <stddef.h>
#include <utf.h>
#include <fmt.h>
#include <math.h>
#include <ctype.h>	/* for tolower */

/*
 * OS-specific crap
 */
#define _NEEDUCHAR 1
#define _NEEDUSHORT 1
#define _NEEDUINT 1
#define _NEEDULONG 1

typedef long p9jmp_buf[sizeof(sigjmp_buf)/sizeof(long)];

#if defined(__linux__)
#	include <sys/types.h>
#	if defined(__USE_MISC)
#		undef _NEEDUSHORT
#		undef _NEEDUINT
#		undef _NEEDULONG
#	endif
#	if defined(__Linux26__)
#		define PLAN9PORT_USING_PTHREADS 1
#	endif
#elif defined(__sun__)
#	include <sys/types.h>
#	undef _NEEDUSHORT
#	undef _NEEDUINT
#	undef _NEEDULONG
#	define PLAN9PORT_USING_PTHREADS 1
#elif defined(__FreeBSD__)
#	include <sys/types.h>
#	include <osreldate.h>
#	if !defined(_POSIX_SOURCE)
#		undef _NEEDUSHORT
#		undef _NEEDUINT
#	endif
#	if __FreeBSD_version >= 500000
#		define PLAN9PORT_USING_PTHREADS 1
#	endif
#elif defined(__APPLE__)
#	include <sys/types.h>
#	undef _NEEDUSHORT
#	undef _NEEDUINT
#	define _NEEDLL 1
#	define PLAN9PORT_USING_PTHREADS 1
#else
	/* No idea what system this is -- try some defaults */
#	define PLAN9PORT_USING_PTHREADS 1
#endif

#ifndef O_DIRECT
#define O_DIRECT 0
#endif

#ifdef PLAN9PORT_USING_PTHREADS
#include <pthread.h>
#endif

typedef signed char schar;
typedef unsigned int u32int;
typedef int s32int;

#ifdef _NEEDUCHAR
	typedef unsigned char uchar;
#endif
#ifdef _NEEDUSHORT
	typedef unsigned short ushort;
#endif
#ifdef _NEEDUINT
	typedef unsigned int uint;
#endif
#ifdef _NEEDULONG
	typedef unsigned long ulong;
#endif
typedef unsigned long long uvlong;
typedef long long vlong;
typedef uvlong u64int;
typedef vlong s64int;
typedef uchar u8int;
typedef schar s8int;
typedef ushort u16int;
typedef short s16int;

#undef _NEEDUCHAR
#undef _NEEDUSHORT
#undef _NEEDUINT
#undef _NEEDULONG

/*
 * Funny-named symbols to tip off 9l to autolink.
 */
#define AUTOLIB(x)	static int __p9l_autolib_ ## x = 1;

#if defined(__cplusplus)
}
#endif
#endif

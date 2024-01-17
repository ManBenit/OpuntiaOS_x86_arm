#ifndef _LIBC_CTYPE_H
#define _LIBC_CTYPE_H

#include <stddef.h>
#include <sys/_structs.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

#define _U 01
#define _L 02
#define _N 04
#define _S 010
#define _P 020
#define _C 040
#define _X 0100
#define _B 0200

extern const char __ctypes[256];

static inline int isalnum(int c) { return __ctypes[(unsigned char)(c)] & (_U | _L | _N); }
static inline int isalpha(int c) { return __ctypes[(unsigned char)(c)] & (_U | _L); }
static inline int iscntrl(int c) { return __ctypes[(unsigned char)(c)] & (_C); }
static inline int isdigit(int c) { return __ctypes[(unsigned char)(c)] & (_N); }
static inline int isxdigit(int c) { return __ctypes[(unsigned char)(c)] & (_N | _X); }
static inline int isspace(int c) { return __ctypes[(unsigned char)(c)] & (_S); }
static inline int ispunct(int c) { return __ctypes[(unsigned char)(c)] & (_P); }
static inline int isprint(int c) { return __ctypes[(unsigned char)(c)] & (_P | _U | _L | _N | _B); }
static inline int isgraph(int c) { return __ctypes[(unsigned char)(c)] & (_P | _U | _L | _N); }
static inline int islower(int c) { return (__ctypes[(unsigned char)(c)] & (_U | _L)) == _L; }
static inline int isupper(int c) { return (__ctypes[(unsigned char)(c)] & (_U | _L)) == _U; }
static inline int tolower(int c) { return isupper(c) ? (c) - 'a' + 'A' : c; }
static inline int toupper(int c) { return islower(c) ? (c) - 'A' + 'a' : c; }

__END_DECLS

#endif /* _LIBC_CTYPE_H */
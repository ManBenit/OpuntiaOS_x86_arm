#ifndef _LIBC_DIRENT_H
#define _LIBC_DIRENT_H

#include <stddef.h>
#include <sys/_structs.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

struct __dirstream {
    int fd;
    size_t size; /* size of dir data */
    size_t allocated; /* size of data holder block */
    size_t offset;
};
typedef struct __dirstream DIR;

struct __dirent {
    uint32_t d_ino; /* Inode number */
    uint32_t d_off; /* Offset to next linux_dirent */
    uint16_t d_reclen; /* Length of this linux_dirent */
    char d_name[]; /* Filename (null-terminated) */
};
typedef struct __dirent dirent_t;

ssize_t getdents(int fd, char* buf, size_t len);

__END_DECLS

#endif /* _LIBC_DIRENT_H */
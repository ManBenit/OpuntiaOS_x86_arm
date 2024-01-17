#include <signal.h>
#include <stdlib.h>
#include <sysdep.h>

void exit(int status)
{
    DO_SYSCALL_1(SYS_EXIT, status);
    __builtin_unreachable();
}

void abort()
{
    raise(SIGABRT);
    exit(127);
}

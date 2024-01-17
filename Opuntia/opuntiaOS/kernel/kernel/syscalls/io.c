/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <io/shared_buffer/shared_buffer.h>
#include <io/sockets/local_socket.h>
#include <libkern/bits/errno.h>
#include <libkern/libkern.h>
#include <libkern/log.h>
#include <mem/kmalloc.h>
#include <platform/generic/syscalls/params.h>
#include <syscalls/handlers.h>
#include <tasking/tasking.h>

void sys_socket(trapframe_t* tf)
{
    proc_t* p = RUNNING_THREAD->process;
    int domain = SYSCALL_VAR1(tf);
    int type = SYSCALL_VAR2(tf);
    int protocol = SYSCALL_VAR3(tf);

    file_descriptor_t* fd = proc_get_free_fd(p);
    if (!fd) {
        return_with_val(-1);
    }

    if (domain == PF_LOCAL) {
        int res = local_socket_create(type, protocol, fd);
        if (!res) {
            return_with_val(proc_get_fd_id(p, fd));
        }
        return_with_val(res);
    }
    return_with_val(-1);
}

void sys_bind(trapframe_t* tf)
{
    proc_t* p = RUNNING_THREAD->process;
    int sockfd = SYSCALL_VAR1(tf);

    file_descriptor_t* sfd = proc_get_fd(p, sockfd);
    if (sfd->file->type != FTYPE_SOCKET || !sfd->file->socket) {
        return_with_val(-EBADF);
    }

    char __user* name = (char __user*)SYSCALL_VAR2(tf);
    size_t len = (size_t)SYSCALL_VAR3(tf);
    char* kname = umem_bring_to_kernel_str_with_len(name, len);

    int ret = 0;
    switch (sfd->file->socket->domain) {
    case PF_LOCAL:
        ret = local_socket_bind(sfd, kname, len);
        break;

    default:
        ret = -EINVAL;
        break;
    }

    kfree(kname);
    return_with_val(ret);
}

void sys_connect(trapframe_t* tf)
{
    proc_t* p = RUNNING_THREAD->process;
    int sockfd = SYSCALL_VAR1(tf);
    file_descriptor_t* sfd = proc_get_fd(p, sockfd);
    if (sfd->file->type != FTYPE_SOCKET || !sfd->file->socket) {
        return_with_val(-EBADF);
    }

    char __user* name = (char __user*)SYSCALL_VAR2(tf);
    size_t len = (size_t)SYSCALL_VAR3(tf);
    char* kname = umem_bring_to_kernel_str_with_len(name, len);

    int ret = 0;
    switch (sfd->file->socket->domain) {
    case PF_LOCAL:
        ret = local_socket_connect(sfd, kname, len);
        break;

    default:
        ret = -EFAULT;
        break;
    }

    kfree(kname);
    return_with_val(ret);
}

void sys_ioctl(trapframe_t* tf)
{
    proc_t* p = RUNNING_THREAD->process;
    file_descriptor_t* fd = proc_get_fd(p, SYSCALL_VAR1(tf));

    if (!fd) {
        return_with_val(-EBADF);
    }

    if (!fd->file->ops->ioctl) {
        return_with_val(-EACCES);
    }
    return_with_val(fd->file->ops->ioctl(fd->file, SYSCALL_VAR2(tf), SYSCALL_VAR3(tf)));
}

void sys_shbuf_create(trapframe_t* tf)
{
    uintptr_t __user* buffer = (uintptr_t __user*)SYSCALL_VAR1(tf);
    size_t size = SYSCALL_VAR2(tf);
    return_with_val(shared_buffer_create(buffer, size));
}

void sys_shbuf_get(trapframe_t* tf)
{
    int id = SYSCALL_VAR1(tf);
    uintptr_t __user* buffer = (uintptr_t __user*)SYSCALL_VAR2(tf);
    return_with_val(shared_buffer_get(id, buffer));
}

void sys_shbuf_free(trapframe_t* tf)
{
    int id = SYSCALL_VAR1(tf);
    return_with_val(shared_buffer_free(id));
}
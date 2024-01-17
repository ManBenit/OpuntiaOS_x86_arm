/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef _KERNEL_IO_SOCKETS_LOCAL_SOCKET_H
#define _KERNEL_IO_SOCKETS_LOCAL_SOCKET_H

#include <io/sockets/socket.h>

int local_socket_create(int type, int protocol, file_descriptor_t* fd);
bool local_socket_can_read(file_t* file, size_t start);
int local_socket_read(file_t* file, void __user* buf, size_t start, size_t len);
bool local_socket_can_write(file_t* file, size_t start);
int local_socket_write(file_t* file, void __user* buf, size_t start, size_t len);
int local_socket_fchmod(file_t* file, mode_t mode);

int local_socket_bind(file_descriptor_t* sock, char* name, size_t len);
int local_socket_connect(file_descriptor_t* sock, char* name, size_t len);

#endif /* _KERNEL_IO_SOCKETS_LOCAL_SOCKET_H */
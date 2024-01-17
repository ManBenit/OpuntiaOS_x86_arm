/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef _KERNEL_TASKING_SIGNAL_H
#define _KERNEL_TASKING_SIGNAL_H

#include <libkern/bits/signal.h>
#include <libkern/types.h>

#define SIGNALS_CNT 32

enum SIGNAL_ACTION {
    SIGNAL_ACTION_ABNORMAL_TERMINATE,
    SIGNAL_ACTION_TERMINATE,
    SIGNAL_ACTION_STOP,
    SIGNAL_ACTION_CONTINUE,
    SIGNAL_ACTION_IGNORE,
};

#endif // _KERNEL_TASKING_SIGNAL_H
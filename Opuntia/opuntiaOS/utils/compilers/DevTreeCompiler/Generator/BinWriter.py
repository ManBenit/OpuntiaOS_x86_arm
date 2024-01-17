# Copyright (C) 2020-2022 The opuntiaOS Project Authors.
#  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
#
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

class BinWriter():
    def __init__(self, output_file):
        self.output_file = output_file

    def write(self, data):
        binfile = open(self.output_file, "wb")
        binfile.write(bytes(data))
        binfile.close()
# Copyright 2021 Nikita Melekhin. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

class Connection:
    def __init__(self, name, magic, protected=False):
        self.name = name
        self.magic = magic
        self.protected = protected
        self.messages = {}
        self.functions = {}

    def add_message(self, msg_name, params):
        if msg_name in self.messages:
            op = self.messages[msg_name]
            if (params != op):
                print("{0} has 2 different params".format(msg1_name))
                exit(1)
        self.messages[msg_name] = params

    def add_function(self, msg1_name, msg2_name=None):
        if msg1_name in self.functions:
            print("{0} has 2 functions".format(msg1_name))
            exit(1)
        self.functions[msg1_name] = msg2_name
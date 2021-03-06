#! /usr/bin/env python
# Copyright 2014 Uri Laserson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import optparse

import vdj
import vdj.pipeline

parser = optparse.OptionParser()
parser.add_option('-b','--basename')
parser.add_option('-p','--packetsize',type='int')
(options, args) = parser.parse_args()

if len(args) == 1:
    inhandle = open(args[0],'r')
elif len(args) == 0:
    inhandle = sys.stdin
else:
    raise Exception, "Too many arguments."

parts = vdj.pipeline.iterator2parts( vdj.parse_imgt(inhandle),
                                     options.basename,
                                     options.packetsize)

for part in parts:
    print part

#!/usr/bin/env python

import sys

array = []
N = 0

for line in sys.stdin:
  data = line.rstrip().split()
  if data[1] != "-nan":
    array.append(data[1])

array.sort( reverse=True)
current = None
count = 0
# print array
N = len(array)
for i in array:
  if current == None:
    current = i
    count = 1
  else:
    if current != i:
      print '%s\t%s' % (current, float(count)/100)
      current = i
      count = 1
    else:
      count += 1
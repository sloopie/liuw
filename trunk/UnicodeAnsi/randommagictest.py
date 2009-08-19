# -*- coding: utf-8 -*-
#!/usr/bin/python

# liuw
# @ LOIS @ CAS

import findmagic
import random
import psyco

psyco.full()

idxl = []

for i in range(10):
    idxl.append(random.randrange(0, 41466))
    

li = []
for i in idxl:
    li.append(N[i])
print ['%04x' % x for x in li]

magic, subset, trans = findmagic.findmagic(N)

if magic:
    print '%04x' % magic
    print ['%04x' % x for x in subset]
    print ['%04x' % x for x in trans]
else:
    print 'no magic found'

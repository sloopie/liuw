# -*- coding: utf-8 -*-
#!/usr/bin/python

# non-recursive combination
# liuw


def MakeCombinationFunction(name, n, k):
    '''
This function returns a function object which will generate indexs
for combination.

name function name
n    total element count
k    take k elements from n, maximum is 20
    '''
    if k > n:
        k = n
    constructs = [('%sfor i%d in xrange(i%d+1, %d):\n'%(' '*(i+1)*4, i+1, i, n),
                   'i%d'%(i+1,))
                  for i in range(k)]
    f, a = map(None, *constructs)
    level = len(constructs)
    f = ' '.join(f)
    source = '    i0 = -1\n' + f + '%syield [%s]' % (' '*4*(level+1), ','.join(a))
    source = 'def %s():\n' % name + source
    scope = {}
    exec source in scope
    return scope[name]


from collection import N
##F = MakeCombinationFunction('F',100, 20)

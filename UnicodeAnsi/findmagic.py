# -*- coding: utf-8 -*-
#!/usr/bin/python
# findmagic.py
# liuw
# @ LOIS @ CAS

from collection import C, N

############# Customized Section ##############
def magicfunc(a, b):
    return a ^ b

M = [0x1000, 0x2000, 0xf004, 0xfe74, 0x4014]
############# Customized Section ##############


def gen_subset(items):
    for a in range(len(items), 0, -1):
        for b in comb(items, a):
            yield b

def comb(items, n=None):
    if n is None:
        n = len(items)
    for i in range(len(items)):
        v = items[i:i+1]
        if n == 1:
            yield v
        else:
            rest = items[i+1:]
            for c in comb(rest, n-1):
                yield v + c
            
def perm(items, n=None):
    if n is None:
        n = len(items)
    for i in range(len(items)):
        v = items[i:i+1]
        if n == 1:
            yield v
        else:
            rest = items[:i] + items[i+1:]
            for p in perm(rest, n-1):
                yield v + p

def findmagic(M, func):
    '''
    M           Magic Number Set
    func        Target Function
    '''
    for subset in gen_subset(M):
        for magic in C:
            trans = [func(i, magic) for i in subset if func(i, magic) in C]
            if len(trans) == len(subset):
                return magic, subset, trans
    return None, None, None


def test():
    magic, subset, trans = findmagic(M, magicfunc)
    if magic is not None:
        print '%04x' % magic
        print ['%04x' % x for x in subset]
        print ['%04x' % x for x in trans]
    else:
        print 'no magic found'
        
if __name__ == '__main__':
    try:
        import psyco
        psyco.full()
        print 'psyco found'
    except:
        print 'psyco not found'
##    import profile
##    profile.run('test()')
    test()


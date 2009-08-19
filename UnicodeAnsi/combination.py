# -*- coding: utf-8 -*-
#!/usr/bin/python

# combination.py

def ByNestedComprehensionAlgorithm(sets):
    '''
    Returns a list of all element combinations from the given sets.
    A combination is represented as a tuple, with the first tuple
    element coming from the first set, the second tuple element
    coming from the second set and so on.
    A set may be any iterable to which the not operator is applicable.
    '''
    g = []
    for set1 in sets:
        if not set1: return []
        if g:
            g = [ i + (j,) for i in g for j in set1]
        else:
            g = [(j,) for j in set1]
    return g


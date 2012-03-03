#!/usr/bin/env python
from vector_ops import get_vector, display_strings, display_ints

if __name__ == '__main__':
    print '''Accessing a Python list created by copying the contents of a C++ vector:'''
    print '   ', get_vector()
    print '------------------------------------------------------------------------'

    print '''\
Using C++ code to display the contents of a C++ vector<int> initialized from
  a list of integers created in Python:
'''
    display_ints([i for i in range(10)])
    print '------------------------------------------------------------------------'

    print '''\
Using C++ code to display the contents of a C++ vector<string> initialized from
  a list of strings created in Python:
'''
    display_strings(['blah %d' % i for i in range(10)])

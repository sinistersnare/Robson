#!/usr/bin/env python3


import unittest

class Tree:
    """Simple binary tree"""
    def __init__(self, data: int, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

def insert(cur, data):
    if cur is None:
        return Tree(data)
    if cur.data > data:
        cur.left = insert(cur.left, data)
    elif cur.data < data:
        cur.right = insert(cur.right, data)
    return cur

def pre_order(cur):
    if cur is None:
        return
    yield cur.data
    pre_order(cur.left)
    pre_order(cur.right)

def in_order(cur):
    if cur is None:
        return
    in_order(cur.left)
    yield cur.data
    in_order(cur.right)

def post_order(cur):
    if cur is None:
        return
    post_order(cur.left)
    post_order(cur.right)
    yield cur.data


class TestPythonTree(unittest.TestCase):
    def test_preorder(self):
        self.assertEqual(True, True)


class TestRobson(unittest.TestCase):
    """
    1) generate list of random numbers.
    2) subprocess('cd .. && make clean && make all && bin/robson.x -rno RANDOM_NUMBERS_FROM_#1')
    3) get output from #2, organize into pre,in,post order lists.
    4) run RANDOM_NUMBERS_FROM_#1 with Tree implementation here.
    5) test #2 lists with #4 data.
    """
    pass



if __name__ == '__main__':
    unittest.main()

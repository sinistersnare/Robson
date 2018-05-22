#!/usr/bin/env python3


import unittest
import random
from subprocess import check_output, run

class Tree:
    """Simple binary tree"""
    def __init__(self, data: int, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

def tree_insert(cur, data):
    if cur is None:
        return Tree(data)
    if cur.data > data:
        cur.left = tree_insert(cur.left, data)
    elif cur.data < data:
        cur.right = tree_insert(cur.right, data)
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


def sort_orders(output):
    pres = []
    ins = []
    posts = []
    for line in output.split('\n'):
        if line.startswith("post:"):
            posts.append(line.split(':')[1])
        elif line.startswith("pre:"):
            pres.append(line.split(':')[1])
        elif line.startswith("in:"):
            ins.append(line.split(':')[1])
        else:
            return (False, False, False)
    return (pres, ins, posts)


class TestPythonTree(unittest.TestCase):
    def test_preorder(self):
        self.assertEqual(True, True)

class TestRobson(unittest.TestCase):
    def test_preorder_random(self):
        tree_values = [random.randint(0, 1000) for i in range(5)]
        print("Values: {}".format(tree_values))
        pytree = None
        for val in tree_values:
            pytree = tree_insert(pytree, val)
        py_pre = list(pre_order(pytree))
        py_in = list(in_order(pytree))
        py_post = list(post_order(pytree))

        command = ['bin/robson.x', '-rno', ]
        command.extend(map(str, tree_values))
        stdout = check_output(command).decode('utf-8')
        pre_values, in_values, post_values = sort_orders(stdout)
        self.assertEqual(py_pre, pre_values)
        self.assertEqual(py_in, in_values)
        self.assertEqual(py_post, post_values)

"""
1) generate list of random numbers.
2) subprocess('cd .. && make clean && make all && bin/robson.x -rno RANDOM_NUMBERS_FROM_#1')
3) get output from #2, organize into pre,in,post order lists.
4) run RANDOM_NUMBERS_FROM_#1 with Tree implementation here.
5) test #2 lists with #4 data.
"""

if __name__ == '__main__':
    unittest.main()

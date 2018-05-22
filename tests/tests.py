#!/usr/bin/env python3


import unittest
import random
from subprocess import check_output, Popen, PIPE

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
    def inner(cur, lst):
        if cur is None:
            return
        lst.append(cur.data)
        inner(cur.left, lst)
        inner(cur.right, lst)
    ordered = []
    inner(cur, ordered)
    return ordered

def in_order(cur):
    def inner(cur, lst):
        if cur is None:
            return
        inner(cur.left, lst)
        lst.append(cur.data)
        inner(cur.right, lst)
    ordered = []
    inner(cur, ordered)
    return ordered

def post_order(cur):
    def inner(cur, lst):
        if cur is None:
            return
        inner(cur.left, lst)
        inner(cur.right, lst)
        lst.append(cur.data)
    ordered = []
    inner(cur, ordered)
    return ordered


def sort_orders(output):
    pres = []
    ins = []
    posts = []
    for line in output.split('\n'):
        if line.startswith("post:"):
            posts.append(int(line.split(':')[1]))
        elif line.startswith("pre:"):
            pres.append(int(line.split(':')[1]))
        elif line.startswith("in:"):
            ins.append(int(line.split(':')[1]))
        else:
            print("BAD INPUT IN sort_orders!!!")
            return (False, False, False)
    return (pres, ins, posts)


class TestPythonTree(unittest.TestCase):
    pass # TODO

class TestRobson(unittest.TestCase):
    def test_traversal_random(self):
        tree_values = [random.randint(0, 100000) for i in range(5000)]
        pytree = None
        for val in tree_values:
            pytree = tree_insert(pytree, val)
        py_pre = pre_order(pytree)
        py_in = in_order(pytree)
        py_post = post_order(pytree)

        command = ['bin/robson.x', '-rno']
        command.extend(map(str, tree_values))
        stdout = check_output(command).decode('utf-8').strip()
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
    cmd = ["make", "clean", "&&", "make", "all"]
    p = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE)
    out, err = p.communicate() # swallow output! TODO: maybe check to make sure it worked?
    unittest.main()

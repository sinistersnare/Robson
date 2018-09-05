#!/usr/bin/env python3

import random
import unittest
from subprocess import check_output, Popen, PIPE

from binary_tree import Tree, tree_insert, pre_order, in_order, post_order

def sort_orders(output):
    """
    Takes the stdout of the default runners for the robson traversal,
    and parses it into the separate lists.
    """
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


def random_binary_tree(max_tree_val, max_tree_size):
    tree_values = [random.randint(0, max_tree_val) for i in range(max_tree_size)]
    pytree = None
    for val in tree_values:
        pytree = tree_insert(pytree, val)
    py_pre = pre_order(pytree)
    py_in = in_order(pytree)
    py_post = post_order(pytree)
    return (tree_values, py_pre, py_in, py_post)

class TestPythonTree(unittest.TestCase):
    """
    Tests the python tree implementation.
    """
    pass # TODO

class TestInversion(unittest.TestCase):

    def test_inversion_random(self):
        tree_values, py_pre, py_in, py_post = random_binary_tree(10000, 5000)

        command = ['bin/link_inversion.x', '-rno']
        command.extend(map(str, tree_values))
        stdout = check_output(command).decode('utf-8').strip()
        pre_values, in_values, post_values = sort_orders(stdout)
        self.assertEqual(py_pre, pre_values)
        self.assertEqual(py_in, in_values)
        self.assertEqual(py_post, post_values)

class TestThreaded(unittest.TestCase):

    def get_output_order(self, output):
        return [int(line) for line in output.split('\n')]

    def test_threaded_random(self):
        tree_values, _, py_in, _ = random_binary_tree(10000, 5000)

        command = ['bin/threaded.x']
        command.extend(map(str, tree_values))
        stdout = check_output(command).decode('utf-8').strip()
        ins = self.get_output_order(stdout)
        self.assertEqual(py_in, ins)


class TestRobson(unittest.TestCase):
    def test_traversal_random(self):
        tree_values, py_pre, py_in, py_post = random_binary_tree(10000, 5000)

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

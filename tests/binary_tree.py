#!/usr/bin/env python3

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

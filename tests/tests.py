

class Tree:
    def __init__(self, val, left, right):
        self.val = val
        self.left = left
        self.right = right


def preorder(cur: Tree):
    if cur is None:
        return
    yield cur.val
    preorder(cur.left)
    preorder(cur.right)

def inorder(cur: Tree):
    if cur is None:
        return
    inorder(cur.left)
    yield cur.val
    inorder(cur.right)

def postorder(cur: Tree):
    if cur is None:
        return
    postorder(cur.left)
    postorder(cur.right)
    yield cur.val



def setup():
    pass

def test_robson():
    pass

def test_inversion():
    pass

def test_threaded():
    pass



def main():
    setup()
    test_robson()
    test_threaded()
    test_inversion()


if __name__ == '__main__':
    main()

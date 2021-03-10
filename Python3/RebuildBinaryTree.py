class TreeNode:
    def __init__(self, data):
        self.val = data
        self.left = None
        self.right = None


pre = input()
mid = input()
pre = pre.split(" ")
mid = mid.split(" ")

stack = list()
lim = len(pre)
im = 0

root = TreeNode(pre[0])
stack = [root]

for i in range(1, len(pre)):
    if stack[-1].val != mid[im]:
        stack.append(TreeNode(pre[i]))
        stack[-2].left = stack[-1]
    else:
        while stack and stack[-1].val == mid[im]:
            tmp = stack.pop()
            im += 1
        tmp.right = TreeNode(pre[i])
        stack.append(tmp.right)


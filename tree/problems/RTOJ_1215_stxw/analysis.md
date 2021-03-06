### RTOJ_1215 - 查找二叉树

[去看题目描述](./description.md)

&emsp;&emsp;这是一道简单的二叉树遍历题，题目要求用中序遍历的方法查找二叉树中特定值的节点。

&emsp;&emsp;首先考虑如何存储二叉树的问题，由于读入的数据包含节点的左孩子和右孩子编号，所以使用二叉树的链式存储方法会更方便一点。可以先声明一个二叉树节点的结构，然后用这个结构创建一个一维数组来存储二叉树，数组的下标对应于二叉树节点的编号。然后读入数据，建立二叉树。

```cpp
typedef struct node
{
	int value; // 值
	int left_no, right_no; // 左右孩子节点编号
} node;

node tree[MAXN];
```

&emsp;&emsp;接下来进行二叉树遍历，这里采用递归遍历的方法（非递归遍历的方法相对麻烦一点），中序遍历大致的过程为：

1. 判读当前树是否为空
2. 遍历左子树
3. 访问当前树的根节点
4. 遍历右子树

```cpp
// x是需要查找的值，pa指向用来统计遍历节点个数的变量
int mid_search(node tree[], int root, int x, int *pa)
{
	// 判断该树是否为空树
	// .....
	// 遍历左子树
	// .....
	// 访问当前根节点
	// .....
	// 遍历右子树
	// .....
	return 0;//没有找到x，返回0
}
```

&emsp;&emsp;第1个过程，判读当前树是否为空，对于本题来说，左右孩子节点编号为0，表示该节点没有左孩子或右孩子，也就是左子树或右子树为空树，所以判读当前树是否为空只需要判读当前树的根节点是否为0就好了。

```cpp
if(root == 0) //判断该树是否为空树
{
	return 0;
}
```

&emsp;&emsp;第2个过程，遍历左子树，只需要将左孩子的节点编号作为根节点，传入递归调用的函数，然后判断在左子树中是否找到就好了。

```cpp
res = mid_search(tree, tree[root].left_no, x, pa);
if(res == 1) // 判断在左子树中是否找到x
{
	return 1; // 在左子树找到了x，返回1
}
```

&emsp;&emsp;第3个过程，访问当前树的根节点，判断根节点的值是否为x，如果是则返回1，表示找到了x，然后`(*pa)++;`，访问的节点个数加1。

```cpp
if(tree[root].value == x) //判断当前节点的值是否为x
{
	return 1; // 找到了x，返回1
}
(*pa)++; //访问的节点个数加1
```

&emsp;&emsp;第4个过程，遍历右子树，和遍历左子树的过程相似，将右孩子的节点编号作为根节点，进行递归遍历就好了。

[去看参考代码](./main.cpp)

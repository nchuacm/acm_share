/* 1215: 查找二叉树 */
#include <stdio.h>

const int MAXN = 100 + 10;

typedef struct node
{
	int value; // 值
	int left_no, right_no; // 左右孩子节点编号
} node;

int mid_search(node tree[], int root, int x, int *pa)
{
	int res = 0;
	if(root == 0) //判断该树是否为空树
	{
		return 0;
	}

	//遍历左子树
	res = mid_search(tree, tree[root].left_no, x, pa);
	if(res == 1) // 判断在左子树中是否找到x
	{
		return 1;
	}

	//访问当前根节点
	(*pa)++; //访问的节点个数加1
	if(tree[root].value == x) //判断当前节点的值是否为x
	{
		return 1;
	}

	//遍历右子树
	res = mid_search(tree, tree[root].right_no, x, pa);
	if(res != 0)
	{
		return 1;
	}
	return 0;//没有找到x，返回0
}

int main()
{
	int n, x, i, res, ans;
	node tree[MAXN];

	scanf("%d", &n);
	scanf("%d", &x);
	for(i = 1; i <= n; i++)
	{
		scanf("%d %d %d", &tree[i].value, &tree[i].left_no, &tree[i].right_no);
	}
	ans = 0;
	res = mid_search(tree, 1, x, &ans);
	if(res == 0)
	{
		printf("no found!\n");
	}
	else
	{
		printf("%d\n", ans);
	}
	return 0;
}

/*

7
15
5 2 3
12 4 5
10 0 0
29 0 0
15 6 7
8 0 0
23 0 0

*/
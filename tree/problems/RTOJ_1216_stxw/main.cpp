/* 1216: 对称二叉树 */
#include <stdio.h>
#include <string.h>

const int MAXN = 1000 + 10;

int search(char tree[], int root)
{
	int num = 0;
	if(tree[root] == '#')//判断该树是否为空树
	{
		return 1;
	}
	if((tree[2 * root] == '#' && tree[2 * root + 1] != '#') ||
		(tree[2 * root] != '#' && tree[2 * root + 1] == '#'))
	{//判断当前节点的左右孩子是否对称
		return 0;
	}
	num += search(tree, 2 * root);//查找左子树
	num += search(tree, 2 * root + 1);//查找右子树
	if(num != 2)//判断左右子树是否有一颗树不是对称二叉树
	{
		return 0;
	}
	return 1;
}

int main()
{
	int ans, len;
	char tree[MAXN];

	memset(tree, '#', sizeof(tree));
	scanf("%s", tree + 1);
	len = strlen(tree);
	tree[len] = '#';

	ans = search(tree, 1);
	if(ans == 1)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
	return 0;
}
/* 1213: FBI树 */
#include <stdio.h>
#include <string.h>

const int MAX_N = 10 + 1;
const int MAX_S = 1 << MAX_N;

void build_tree(char str[], int left, int right, char tree[], int root)
{
	int mid = (left + right) / 2;
	if(right - left <= 1)//判断该树对应的串长度是否为1，
	{                    //如果是，则该节点为叶子节点
		tree[root] = (str[left] == '0') ? 'B' : 'I';
		return ;
	}
	build_tree(str, left, mid, tree, root * 2);//递归建立左右子树
	build_tree(str, mid, right, tree, root * 2 + 1);
	// 判断该节点的是否是F类型节点
	if(tree[root * 2] == tree[root * 2 + 1])
	{
		tree[root] = tree[root * 2];
	}
	else
	{
		tree[root] = 'F';
	}
}

void post_travel(char tree[], int root)
{
	if(tree[root] != '#')
	{
		post_travel(tree, root * 2);
		post_travel(tree, root * 2 + 1);
		printf("%c", tree[root]);
	}
}

int main()
{
	int n, s_len;
	char str[MAX_S];
	char tree[2 * MAX_S];

	scanf("%d", &n);
	getchar();
	scanf("%s", str);

	s_len = strlen(str);
	memset(tree, '#', sizeof(tree));
	//建立二叉树
	build_tree(str, 0, s_len, tree, 1);
	//后序遍历二叉树
	post_travel(tree, 1);
	printf("\n");
	return 0;
}
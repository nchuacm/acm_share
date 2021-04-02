/* 1621: 找树根和孩子 */
#include <stdio.h>
#include <string.h>

const int MAXN = 1000 + 10;

int main()
{
	int n, m, x, y;
	int i, num, root, max_no, max;
	int tree[MAXN];
	int child_num[MAXN];
	memset(tree, -1, sizeof(tree)); //将tree初始化为全-1
	memset(child_num, 0, sizeof(child_num)); //将child_num初始化为全0
	
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++)
	{
		scanf("%d %d", &x, &y);
		tree[y] = x;
		child_num[x]++;
	}

	//查找根节点
	root = x;
	//如果tree[root] == -1，则该节点是根节点
	while(tree[root] != -1)
	{
		root = tree[root]; //继续查找该节点的父节点
	}
	printf("%d\n", root);

	//遍历所有节点的孩子个数，找孩子个数最多的那个节点
	max = -1;
	for(i = 1; i < MAXN; i++)
	{
		if(child_num[i] > max)
		{
			max = child_num[i];
			max_no = i;
		}
	}
	printf("%d\n", max_no);

	//输出max_no的所有孩子
	for(i = 1; i < MAXN; i++)
	{
		if(tree[i] == max_no)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
	return 0;
}
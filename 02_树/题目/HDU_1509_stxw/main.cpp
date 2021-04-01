/* 1622: 单词查找树 */
#include <stdio.h>
#include <string.h>

const int MAX_N = 100000 + 10;
const int MAX_W = 26;
const int MAX_L = 65;

typedef struct trie
{
	char first_ch;//字符集的第一个字符
	int len;//字典树的节点个数
	int node[MAX_N][MAX_W];//字典树的结构
} trie;

void insert_word(char str[], trie *tree)
{
	int i, s_len, x, p;

	p = 0;//初始时，p指向根节点
	s_len = strlen(str);
	for(i = 0; i < s_len; i++)
	{
		x = str[i] - tree->first_ch;//x表示str[i]是字符集的第几个字符
		if(tree->node[p][x] == -1)//判断该字符是否存在
		{
			tree->node[p][x] = tree->len;//向字典树中添加一个节点
			memset(tree->node[tree->len], -1, sizeof(tree->node[tree->len]));
			tree->len++;
		}
		p = tree->node[p][x];//p指向下一个字符
	}
}

int main()
{
	char str[MAX_L];
	trie tree;

	tree.len = 1;//初始时只包含根节点
	tree.first_ch = 'A';//在本题中字符集为A到Z之间的大写字母，A是字符集的第一个字符
	memset(tree.node[0], -1, sizeof(tree.node[0]));//初始化根节点的孩子节点指针为-1
	while(scanf("%s", str) != EOF)
	{
		//向字典树里插入一个单词
		insert_word(str, &tree);
		// if(strcmp(str, "#") == 0)
		// {
		// 	break;
		// }
	}
	printf("%d\n", tree.len);
	return 0;
}
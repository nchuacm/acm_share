### RTOJ_1622 - 单词查找树

[去看题目描述](./description.md)

&emsp;&emsp;本题需要构造一种叫单词查找树的数据结构，单词查找树也叫做字典树或Trie树，在接下来的解析中，我统一用字典树这个名字。

&emsp;&emsp;大致的思路是，按照题目的描述，模拟建立一颗字典树，然后算出字典树的节点个数就好了。对于二叉树来说，每个节点最多有两个孩子，而字典树的每个节点最多可以有n个孩子（n指字符集包含的字符个数），因此，我们可以把字典树看做是一颗n叉树。

&emsp;&emsp;首先，我们来声明一颗单词查找树，声明的代码如下，字典树的node属性是用来存放字典树的结构的，node是一个二维数组，第一维表示字典树的第几个节点，第二维表示该节点的子节点是第几个字符。以题目图中的字典树为例，我们把root节点的编号设为0，则node[0]就表示root节点，因为root节点共有两个子节点A和B，A和B分别是字符集里第0、第1个字符，因此node[0][0]应该存放root的A子节点的编号，node[0][1]应该存放root的B子节点的编号，其他位置因为没有子节点，我们可以用-1来表示。

```cpp
const int MAX_N = 100000 + 10; // 字典树的最大节点数
const int MAX_W = 26; // 字符集包含的字符个数，在本题中，字符集为A到Z之间的大写字母，共26字符。

typedef struct trie
{
	char first_ch; // 字符集的第一个字符
	int len; // 字典树的节点个数
	int node[MAX_N][MAX_W]; // 字典树的结构
} trie;

trie tree;
tree.len = 1; // 初始时只包含根节点
tree.first_ch = 'A'; // 在本题中，A是字符集的第一个字符
```

&emsp;&emsp;接下来，我们写一个向字典树里插入一个单词的函数。插入单词的大致过程是，将该单词按字符出现的顺利作为一条字典树的路径，将这条路径遍历一遍，如果路径中某个节点不存在，则向字典树中插入一个节点，作为那个不存在的节点。

```cpp
void insert_word(char str[], trie *tree)
{
	int i, s_len, x, p;

	p = 0;//初始时，p指向根节点
	s_len = strlen(str);
	for(i = 0; i < s_len; i++)
	{
		x = str[i] - tree->first_ch;//x表示str[i]是字符集的第几个字符
		if(tree->node[p][x] == -1)//判断字典树中该字符是否存在
		{
			//向字典树中添加一个节点
			tree->node[p][x] = tree->len;
			memset(tree->node[tree->len], -1, sizeof(tree->node[tree->len]));
			tree->len++;
		}
		p = tree->node[p][x];//p指向下一个字符
	}
}
```

&emsp;&emsp;完成了上面的部分，最后的main函数里的内容就很容易了，只需要将输入的单词都插入字典树里，最后输出tree.len就好了。

[去看参考代码](./main.cpp)

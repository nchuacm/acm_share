### RTOJ_1621 - 找树根和孩子

[去看题目描述](./description.md)

&emsp;&emsp;在做这题之前需要介绍一种树的存储结构：双亲表示法。

&emsp;&emsp;这种存储结构很简单，对于树中的每个节点，把它的父节点地址记录下来就好了，如果是根节点，则假设它的父节点是-1。下面是一个例子：

![](./parental_representation.png)

&emsp;&emsp;在上图中，2、3、4号节点的父节点是1号节点，所以数组下标为2、3、4的地方的值是1，5到10节点也是同理，1号节点是树的根节点，所以数组下标为1的地方值是-1。

&emsp;&emsp;这就是双亲表示法，是不是很简单？接下来我们使用这种树的存储结构来解决这道题。

&emsp;&emsp;首先是存建立树的结构，我们需要一个数组tree，用来以双亲表示法存储树的结构，因为节点编号最大是1000，所以这个数组的大小至少要是1001，在没有建立树之前，tree可以初始化为全-1，表示不存在任何父子节点关系。其次我们还需要一个数组child_num，用来记录每个节点的孩子个数，方便我们找到孩子最多的节点，大小也至少是1001，child_num要初始化为全0。

&emsp;&emsp;对于每个输入x、y，因为x是y的父节点，按照双亲表示法，我们要让tree数组下标为y的值为x，所以需要执行`tree[y] = x;`，同时，x的子节点个数加1，`child_num[x]++;`。

```cpp
const int MAXN = 1000 + 10;

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
```

&emsp;&emsp;建立好树的结构后，我们来解决第一个问题，找树的根节点。只需要任选一个节点作为当前查找节点，判断该节点是否为根节点，也就是判断tree数组对应的下标值是否为-1，如果是就结束查找，如果不是，就将该节点的父节点作为当前查找节点，继续判断是否为根节点...这样循环下去我们就能找到根节点了。

```cpp
root = x;
//如果tree[root] == -1，则该节点是根节点
while(tree[root] != -1)
{
	root = tree[root]; //继续查找该节点的父节点
}
printf("%d\n", root);
```

&emsp;&emsp;第二个问题，找孩子最多的节点，这个问题就很简单了，只需要遍历一般child_num数组，值最大的，就说明孩子最多。

```cpp
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
```

&emsp;&emsp;第三个问题，输出孩子最多的节点的所有孩子，也就是max_no的所有孩子，这个也很简单，只需要遍历一遍tree数组，如果`tree[i] == max_no`，说明i的父节点是max_no，也就是说i是max_no孩子，将i输出。

```cpp
for(i = 1; i < MAXN; i++)
{
	if(tree[i] == max_no)
	{
		printf("%d ", i);
	}
}
```

[去看参考代码](./main.cpp)

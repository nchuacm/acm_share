### RTOJ_1208 - 奇怪的电梯

[去看题目描述](./description.md)

&emsp;&emsp;本题可以用广度优先搜索算法来解决，广度优先搜索算法需要用队列来实现。首先需要定义一个搜索用的队列，队列中的每个元素需要保存搜索到该楼层的楼层号和到达该楼层的最少按键次数，还需要定义一个数组，用来标记楼层是否被访问过。

```cpp
typedef struct node
{
	int no; // 搜索到该楼层的楼层号
	int step; // 到达该楼层的最少按键次数
} node;

node que[MAX_N]; // 搜索用的队列
int front = 0, back = 0; // 队头和队尾指针

int vis[MAX_N]; // 用来标记楼层是否被访问过
```

&emsp;&emsp;搜索前需要对vis数组初始化，也就是将起始楼层以外的其他楼层都标记为未访问过，然后将起始楼层加入队列。

```cpp
// 初始化vis数组
memset(vis, 0, sizeof(vis));
vis[a] = 1;

// 将起始楼层加入队列
que[back].no = a;
que[back].step = 0;
back++;
```

&emsp;&emsp;接下来开始遍历，对于每一层楼，都有两种选择，向上或者向下，两种选择分别搜索一下就好了。遍历的大致过程如下：

```cpp
// 搜索楼层，直达没有楼层可以加入队列了，队列为空时说明起点能到达的楼层都访问过了
while(front != back)
{
	int front_no = que[front].no; // 获取队头楼层的楼层号
	int front_step = que[front].step; // 获取到达队头楼层的最少按键次数

	int next_no = front_no + k[front_no]; // 计算该楼层向上能到达的楼层
	// .... // 搜索next_no楼层

	next_no = front_no - k[front_no]; // 计算该楼层向下能到达的楼层
	// .... // 搜索next_no楼层

	front++; //将队头楼层出队
}
```

&emsp;&emsp;搜索next_no楼层时，首先需要判断next_no是否是目标楼层，如果是，说明已经找到了用最少按键次数，从起始楼层到达目标楼层的方法，可以结束搜索了。接下来判断next_no是否在[1, n]范围内，且是否被访问过，如果都没有，则将next_no楼入队，然后将其标记为已访问过。

```cpp
if(next_no == b) // 判断next_no是否是目标楼层
{
	ans = front_step + 1;
	break; // 退出搜索
}
// 判断next_no是否在[1, n]范围内，是否被访问过
if(next_no <= n && vis[next_no] == 0)
{
	// 将next_no入队
	que[back].no = next_no;
	que[back].step = front_step + 1;
	back++;
	// 标记为已访问过
	vis[next_no] = 1;
}
```

&emsp;&emsp;结束了搜索后，如果队列为空，则说明是通过`while(front != back)`条件不成立退出的搜索，这是因为将起始楼层能到达的楼层都访问过后，仍然没有找到目标楼层，这时按题目要求输出-1就好了。如果队列不为空，说明是找到楼层后，通过`break;`退出的搜索，这时输出最少按键次数。

```cpp
if(front == back)
{
	printf("-1\n");
}
else
{
	printf("%d\n", ans);
}
```

[去看参考代码](./main.cpp)

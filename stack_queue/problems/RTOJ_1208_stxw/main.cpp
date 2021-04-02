#include <stdio.h>
#include <string.h>

const int MAX_N = 200 + 10;

typedef struct node
{
	int no; // 搜索到该楼层的楼层号
	int step; // 到达该楼层的最少按键次数
} node;

int main()
{
	int i, n, a, b, ans;
	int k[MAX_N];
	int vis[MAX_N]; // 用来标记楼层是否搜索过
	node que[MAX_N];
	int front = 0, back = 0; // 队头和队尾指针

	scanf("%d %d %d", &n, &a, &b);
	for(i = 1; i <= n; i++)
	{
		scanf("%d", &k[i]);
	}

	if(a == b)
	{
		printf("0\n");
		return 0;
	}

	// 初始化vis数组
	memset(vis, 0, sizeof(vis));
	vis[a] = 1;

	// 将起点楼层加入队列
	que[back].no = a;
	que[back].step = 0;
	back++;

	// 搜索楼层，直达没有楼层可以加入队列了，队列为空时说明起点能到达的楼层都访问过了
	while(front != back)
	{
		int front_no = que[front].no; // 获取队头楼层的楼层号
		int front_step = que[front].step; // 获取到达队头楼层的最少按键次数

		int next_no = front_no + k[front_no]; // 计算该楼层向上能到达的楼层
		if(next_no == b) // 判断next_no是否是目标楼层
		{
			ans = front_step + 1;
			break; // 退出搜索
		}
		// 判断next_no是否在$[1, n]$范围内，是否被访问过
		if(next_no <= n && vis[next_no] == 0)
		{
			// 将next_no入队
			que[back].no = next_no;
			que[back].step = front_step + 1;
			back++;
			// 标记为已访问过
			vis[next_no] = 1;
		}

		next_no = front_no - k[front_no]; // 计算该楼层向下能到达的楼层
		if(next_no == b)
		{
			ans = front_step + 1;
			break;
		}
		if(1 <= next_no && vis[next_no] == 0)
		{
			que[back].no = next_no;
			que[back].step = front_step + 1;
			back++;
			vis[next_no] = 1;
		}

		front++; //将队头楼层出队
	}

	if(front == back)
	{
		printf("-1\n");
	}
	else
	{
		printf("%d\n", ans);
	}
	return 0;
}
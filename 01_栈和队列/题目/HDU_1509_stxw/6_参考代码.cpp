#include <stdio.h>
#include <string.h>

const int MAX_N = 10000 + 10;
const int MAX_K = 20;

// 将字符串转化为整数
int string_to_int(char str[], int len)
{
	int i, num = 0;
	for(i = len - 1; i >= 0; i--)
	{
		num = num * 10 + (int)(str[i] - '0');
	}
	return num;
}

int main()
{
	int k, x, y;
	int i, j, len, num;
	char n[10]; // 输入的数字
	char mp[MAX_K][2]; // 变换规则

	char que[MAX_N][10];
	int front = 0, back = 0;
	int vis[MAX_N];

	scanf("%s", n);
	scanf("%d", &k);
	for(i = 0; i < k; i++)
	{
		scanf("%d %d", &x, &y);
		mp[i][0] = (char)('0' + x); // 变换前的数字
		mp[i][1] = (char)('0' + y); // 变换后的数字
	}

	len = strlen(n);
	memset(vis, 0, sizeof(vis));
	num = string_to_int(n, len);
	vis[num] = 1;

	strcpy(que[back], n);
	back++;
	while(front != back)
	{
		char src[10], dst[10];
		strcpy(src, que[front]);

		for(i = 0; i < len; i++)
		{
			for(j = 0; j < k; j++)
			{
				if(src[i] == mp[j][0])
				{
					strcpy(dst, src);
					dst[i] = mp[j][1];
					num = string_to_int(dst, len);
					if(vis[num] == 0)
					{
						strcpy(que[back], dst);
						back++;
						vis[num] = 1;
					}
				}
			}
		}
		front++;
	}

	printf("%d\n", back);
	return 0;
}
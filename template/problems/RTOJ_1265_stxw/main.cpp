#include <stdio.h>

const int MAX_N = 255 + 10;

int main()
{
	int i, ans = 1;
	char str[MAX_N];
	char stack[MAX_N];// 声明一个栈，用stack数组来存储栈里的元素
	int top = -1;// 表示栈顶元素指针，top==-1表示栈为空

	scanf("%s", str);
	for(i = 0; str[i] != '@' && ans != 0; i++)
	{
		if(str[i] == '(')
		{
			top++;
			stack[top] = '(';
		}
		else if(str[i] == ')')
		{
			if(top != -1)
			{
				top--;
			}
			else
			{
				ans = 0;
				break;
			}
		}
	}
	if(top == -1 && ans != 0)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
	return 0;
}

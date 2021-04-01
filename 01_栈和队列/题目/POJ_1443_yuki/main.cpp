#include <stdio.h>
#include <string.h>
#include <math.h>

const int MAX_LEN = 100;
const int ST_MAX = 100;

// 运算符的优先级映射数组
int opt_priority_map[256];

// 初始化运算符的优先级('+' == '-' < '*' == '/' < '^')
void init()
{
	memset(opt_priority_map, -1, sizeof(opt_priority_map));
	opt_priority_map['+'] = 1;
	opt_priority_map['-'] = 1;
	opt_priority_map['*'] = 2;
	opt_priority_map['/'] = 2;
	opt_priority_map['^'] = 3;
}

// 计算a对b进行opt运算的结果
int cal_opt(int a, int b, char opt)
{
	int c;
	if (opt == '+')
	{
		c = a + b;
	}
	else if (opt == '-')
	{
		c = a - b;
	}
	else if (opt == '*')
	{
		c = a * b;
	}
	else if (opt == '/')
	{
		c = (int)(a / b);
	}
	else if (opt == '^')
	{
		c = (int)pow(a, b);
	}
}

// 用操作数栈和运算符栈进行一次运算
void run_cal(char st_opt[], int *st_opt_top, int st_num[], int *st_num_top)
{
	int a, b, c;
	char opt;
	// 从操作数栈中取两个数，并出栈
	b = st_num[*st_num_top];
	(*st_num_top)--;
	a = st_num[*st_num_top];
	(*st_num_top)--;

	// 从运算符栈中取出栈顶运算符，并出栈
	opt = st_opt[*st_opt_top];
	(*st_opt_top)--;

	// 计算a对b进行opt运算的结果
	c = cal_opt(a, b, opt);

	// 将运算的结果存入操作数栈中
	(*st_num_top)++;
	st_num[*st_num_top] = c;
}

int calculate(char str[])
{
	int i, len, k;
	// 声明运算符栈
	char st_opt[ST_MAX];
	int st_opt_top = -1;
	// 声明操作数栈
	int st_num[ST_MAX];
	int st_num_top = -1;

	len = strlen(str);
	for (i = 0; i < len; i++)
	{
		// 如果str[i]是数字
		if ('0' <= str[i] && str[i] <= '9')
		{
			// 将字符串转换为正整数，存入k中
			k = 0;
			while ('0' <= str[i] && str[i] <= '9')
			{
				k = k * 10 + (int)(str[i] - '0');
				i++;
			}

			// 将正整数k存入操作数栈中
			st_num_top++;
			st_num[st_num_top] = k;
		}

		// 如果str[i]是运算符
		if (opt_priority_map[str[i]] != -1)
		{
			// opt_priority_map[str[i]]表示str[i]的优先级
			// opt_priority_map[st_opt[st_opt_top]]表示运算符栈的栈顶运算符的优先级
			// 进行运算，直到运算符栈为空，或者str[i]的优先级大于运算符栈的栈顶运算符的优先级，
			while (st_opt_top != -1 && opt_priority_map[str[i]] <= opt_priority_map[st_opt[st_opt_top]])
			{
				// 进行一次运算
				run_cal(st_opt, &st_opt_top, st_num, &st_num_top);
			}

			// 将str[i]存入运算符栈中
			st_opt_top++;
			st_opt[st_opt_top] = str[i];
		}

		// 如果str[i]是左括号
		if (str[i] == '(')
		{
			// 直接将其入栈
			st_opt_top++;
			st_opt[st_opt_top] = '(';
		}

		// 如果str[i]是右括号
		if (str[i] == ')')
		{
			// 进行运算，直到运算符栈的栈顶为左括号
			while(st_opt[st_opt_top] != '(')
			{
				run_cal(st_opt, &st_opt_top, st_num, &st_num_top);
			}

			// 将左括号出栈
			st_opt_top--;
		}
	}

	while(st_opt_top != -1)
	{
		run_cal(st_opt, &st_opt_top, st_num, &st_num_top);
	}
	return st_num[st_num_top];
}

int main()
{
	int ans;
	char str[MAX_LEN];

	init();
	scanf("%s", str);
	ans = calculate(str);
	printf("%d\n", ans);
	return 0;
}

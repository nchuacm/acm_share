### RTOJ_1827 - 计算

[去看题目描述](./description.md)

&emsp;&emsp;计算字符串类型的算术表达式的结果是栈的一个重要运用，本题就是一个简单的例子。

&emsp;&emsp;在解析输入的字符串前，需要先建立一个运算符优先级映射数组，代码如下：

```cpp
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
```

&emsp;&emsp;建立好运算符优先级映射数组后，对于一个字符类型的运算符opt，就可以用`opt_priority_map[opt]`来获取opt的优先级了。因为加法和减法的优先级最低，所以设置为1；幂运算最高，设置为3；乘法和除法优先级处于它们之间，设置为2。

&emsp;&emsp;接下来需要声明运算符的对两个数进行运算的函数：

```cpp
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
```

&emsp;&emsp;最后还需要声明两个栈，一个用来存操作数，一个用来存运算符。

```cpp
// 声明运算符栈
char st_opt[ST_MAX];
int st_opt_top = -1;
// 声明操作数栈
int st_num[ST_MAX];
int st_num_top = -1;
```

&emsp;&emsp;完成了上述工作，就可以开始解析算术表达式字符串了，方法是用for循环遍历一遍字符串，对于遇到的每一个字符分四种情况：操作数、运算符、左括号、右括号。

```cpp
len = strlen(str);
for (i = 0; i < len; i++)
{
	// 如果str[i]是数字
	if ('0' <= str[i] && str[i] <= '9')
	{
		//某些操作.....
	}

	// 如果str[i]是运算符
	if (opt_priority_map[str[i]] != -1)
	{
		//某些操作.....
	}

	// 如果str[i]是左括号
	if (str[i] == '(')
	{
		//某些操作.....
	}

	// 如果str[i]是右括号
	if (str[i] == ')')
	{
		//某些操作.....
	}
}
```

&emsp;&emsp;对于第一种情况——str[i]是操作数。就将字符类型的整数转化为整形变量，然后将这个整形变量存入操作数栈。

```cpp
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
```

&emsp;&emsp;在讲解第二种情况的处理方法前，先解释一下什么是进行一次运算。进行一次运算是指从操作数栈中取出两个操作数a和b，并将a和b出栈，然后从运算符栈中取出一个运算符opt，将opt出栈，最后对a和b进行opt运算，得到的结果存入操作数栈中。进行一次运算的函数代码如下：

```cpp
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
```

&emsp;&emsp;接下来是第二种情况——str[i]是运算符。如果运算符栈是空栈，那么直接将运算符入栈。如果不是，则比较一下str[i]和运算符栈的栈顶运算符的优先级，如果str[i]的优先级比运算符栈的栈顶运算符的优先级低，或者相等，则进行一次运算，直到str[i]的优先级比运算符栈的栈顶运算符的优先级高，或者运算符栈是空栈时，停止运算。最后将将str[i]存入运算符栈中。这样做的原因是，如果运算符栈的栈顶运算符的优先级比str[i]高，则进行该运算的运算顺序应该在str[i]前面；如果它们的优先级相等，由于运算符栈的栈顶运算符比str[i]先进入运算符，说明它在算术表达式中出现得比str[i]早，根据从左到右的运算规则，他的运算顺序也应该在str[i]前面。经过这样处理就可以保证运算符栈里的运算符优先级是从小到大存储的。

```cpp
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
```

&emsp;&emsp;对于第三种情况——str[i]是左括号，这种情况就很简单了，直接存入运算符栈就OK了。

```cpp
// 直接将其入栈
st_opt_top++;
st_opt[st_opt_top] = '(';
```

&emsp;&emsp;对于第四种情况——str[i]是右括号。这种情况和第二种情况的处理方式类似，如果运算符栈的栈顶运算符不是左括号的话，就进行运算，直到栈顶运算符是左括号为止，最后将左括号从运算符栈出栈就好了。因为，括号内的表达式的运算优先级要比括号外的高，所以要先算出括号内表达示的结果，再进行后面的运算。代码如下：

```cpp
// 进行运算，直到运算符栈的栈顶为左括号
while(st_opt[st_opt_top] != '(')
{
	run_cal(st_opt, &st_opt_top, st_num, &st_num_top);
}

// 将左括号出栈
st_opt_top--;
```

&emsp;&emsp;针对上述的四种情况，在遍历算术表达式字符串的时候，分情况处理一下。遍历完整个字符串后，还需要将运算符栈中剩余的运算符运算完，代码如下：

```cpp
while(st_opt_top != -1)
{
	run_cal(st_opt, &st_opt_top, st_num, &st_num_top);
}
```

&emsp;&emsp;最后，操作数栈中应该只剩下一个操作数，也就是整个算术表达式的运算结果了。

[去看参考代码](./main.cpp)

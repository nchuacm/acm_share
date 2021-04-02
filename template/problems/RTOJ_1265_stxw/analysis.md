### RTOJ_1265 - 括号匹配

[去看题目描述](./description.md)

&emsp;&emsp;本题可以用栈和其基本操作来解决。首先声明一个字符类型的栈。

```cpp
char stack[MAX_N];// 声明一个栈，用stack数组来存储栈里的元素
int top = -1;// 表示栈顶元素指针，top==-1表示栈为空
```

&emsp;&emsp;然后遍历输入的字符串，如果遇到左括号就将其入栈。

```cpp
if(str[i] == '(') // 如果遇到左括号
{
	// 将左括号入栈
	top++;
	stack[top] = '(';
}
```

&emsp;&emsp;如果遇到右括号，则判断栈是否为空，如果不为空，说明该右括号能和上一个入栈的左括号匹配，接下来出栈一个左括号，继续遍历字符串中的下一个字符。如果栈为空，说明该右括号前面没有可以与其匹配的左括号，也就是匹配出错，接下来就可以结束遍历，输出`NO`了。

```cpp
if(str[i] == ')') // 如果遇到右括号
{
	if(top != -1) // 判断栈是否为空
	{
		top--; // 出栈一个左括号
	}
	else
	{
		ans = 0; // 标记匹配出错
		break;
	}
}
```

&emsp;&emsp;如果遍历完整个字符串后，栈为空，且匹配时没有出错，就可以输出`YES`了，这里要判断栈是否为空是为了避免栈中存在还未匹配的左括号的情况，比如输入字符串是`(1+1)((`时，在遍历字符串时虽然没有出现匹配出错，但是最后两个左括号还没有被匹配掉。

```cpp
if(top == -1 && ans != 0)
{
	printf("YES\n");
}
else
{
	printf("NO\n");
}
```

[去看参考代码](./main.cpp)
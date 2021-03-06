### RTOJ_2001 - 水明的账单

[去看题目描述](./description.md)

&emsp;&emsp;本题需要用到优先队列来解决，优先队列可以看成是一种特殊的队列。普通队列的特性是，出队时出队的元素是队列中最先入队的元素；优先队列的特性是，无论队列中元素的入队顺序是怎样的，出队时出队的元素是队列中优先级最大的元素。这个优先级是可以设置的，如果设置成元素的值越大，优先级越高，那么优先队列在出队时出队的元素就是队列中值最大的元素。相反的如果设置成值越小，优先级越小，出队时出队的元素就是队列中值最小的元素。优先队列一般用一种叫“堆”的数据结构来实现，使用堆可以降低获取队列中优先级最元素的时间复杂度，C++中的STL库中已经封装好了一个优先队列，可以直接使用，下面是C++中使用STL库来声明优先队列的代码。

```cpp
#include <queue> //使用优先队列需要添加queue头文件
#include <vector>

using namespace std;

//声明一个值越大，优先级越大的优先队列，每次出队的元素是队列中值最大的元素
priority_queue<int, vector<int>, less<int> > max_q;

//声明一个值越小，优先级越大的优先队列，每次出队的元素是队列中值最小的元素
priority_queue<int, vector<int>, greater<int> > min_q;
```

&emsp;&emsp;上面的代码中`priority_queue`是声明优先队列的关键字，`priority_queue`有三个模板类型的参数，第一个参数是优先队列中元素的数据类型，第二个参数是存放元素使用的容器，一般使用`vector`就好的，第三个参数用于指定优先级规则。`less`和`greater`是`<queue>`定义的两个仿函数，可以理解为两种优先级规则，`less`是值越大，优先级越大的规则；`greater`是值越小，优先级越大的规则。使用这两种规则要保证元素之间是可以用`<`来进行比较，如果不能用`<`来进行比较的话，就需要重载`<`运算符了，关于重载运算符这里就不在详细讲述了。`priority_queue`的三个模板参数里，第一个参数是必要的，其他两个是可选的，第二个参数默认是`vector`，第三个参数默认是`less`，所以以下三行代码是等效的。

```cpp
priority_queue<int, vector<int>, less<int> > max_q;
priority_queue<int, vector<int> > max_q;
priority_queue<int> max_q;
```

&emsp;&emsp;这里需要注意的是，后面的两个右尖括号之间要用空格隔开，不能写成`>>`，因为`>>`是C++里的位右移运算符，部分编译器会报错。下面是关于优先队列的一个实验代码，读者可以编译执行一下，看看输出结果是什么。

```cpp
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

int main()
{
	priority_queue<int, vector<int>, less<int> > max_q;
	max_q.push(3); // 入队一个元素
	max_q.push(8);
	max_q.push(2);
	max_q.push(5);
	printf("less: ");
	while(max_q.empty() == false) // 判断队列是否为空
	{
		printf("%d ", max_q.top()); // 取队头元素
		max_q.pop(); // 出队一个元素
	}
	printf("\n");

	priority_queue<int, vector<int>, greater<int> > min_q;
	min_q.push(3);
	min_q.push(8);
	min_q.push(2);
	min_q.push(5);
	printf("greater: ");
	while(min_q.empty() == false)
	{
		printf("%d ", min_q.top());
		min_q.pop();
	}
	printf("\n");

	return 0;
}
```

&emsp;&emsp;关于优先队列的介绍就到这里了。回到题目上来，这题如果用暴力来解决的话会超时，如果用优先队列优化的话就能过。解法很简单，先声明一个值越大，优先级越大的和一个值越小优先级越小的优先队列，当收到账单时，将其放入两个优先队列中，当要支付账单时，输出两个优先队列中的队头元素，然后出队就好了，代码如下。

```cpp
scanf("%d", &n);
for(i = 0; i < n; i++)
{
	scanf("%d", &m);
	for(j = 0; j < m; j++)
	{
		scanf("%d", &k);
		min_q.push(k);
		max_q.push(k);
	}
	printf("%d %d\n", min_q.top(), max_q.top());
	min_q.pop();
	max_q.pop();
}
```

[去看参考代码](./main.cpp)

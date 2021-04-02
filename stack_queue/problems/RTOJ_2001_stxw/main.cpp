#include <stdio.h>
#include <string.h>

const int MAX_N = 1500000;
// const int MAX_N = 15;

int a[MAX_N], an;
int book[MAX_N];

int main()
{
	int n, m, k;
	int i, j, max, min;

	scanf("%d", &n);
	a[0] = -1;
	a[1] = 1e9;
	an = 2;
	memset(book, 0, sizeof(book));
	for(i = 0; i < n; i++)
	{
		scanf("%d", &m);
		for(j = 0; j < m; j++)
		{
			scanf("%d", &k);
			a[an] = k;
			an++;
		}
		max = 0;
		min = 1;
		for(j = 2; j < an; j++)
		{
			if(book[j] == 0)
			{
				if(a[j] > a[max])
				{
					max = j;
				}
				if(a[j] < a[min])
				{
					min = j;
				}
			}
		}
		printf("%d %d\n", a[min], a[max]);
		book[min] = 1;
		book[max] = 1;
	}
	return 0;
}
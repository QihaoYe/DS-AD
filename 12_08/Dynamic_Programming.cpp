#include <iostream>
// source:http://blog.csdn.net/u010607947/article/details/78326590

using namespace std;

// // Method_1
// int main(int argc, char const *argv[])
// {
// 	int a[] = {0, 3, -4, 5, 1, 3, -7, 2, 1, -2, 3};
// 	int n = 10;
// 	int start = 0;
// 	int end = 0;
// 	int max = INT_MIN;
// 	int sum;
// 	for (int i = 1; i <= n; i++)
// 	{
// 		sum = 0;
// 		for (int j = i; j <= n; j++)
// 		{
// 			sum += a[j];
// 			if (sum > max)
// 			{
// 				start = i;
// 				end = j;
// 				max = sum;
// 			}
// 		}
// 	}
// 	printf("start: %d\nend  : %d\nmax  : %d\n", start, end, max);
// 	return 0;
// }

// // Method_2
// int maxInterval(int * a, int left, int right)
// {
// 	if (left == right)
// 		return a[left];
// 	int center = (left + right) / 2;
// 	int leftMaxInterval = maxInterval(a, left, center);
// 	int rightMaxInterval = maxInterval(a, center + 1, right);

// 	int sum = 0;
// 	int left_max = INT_MIN;
// 	for (int i = center; i >= left; --i)
// 	{
// 		sum += a[i];
// 		if (sum > left_max)
// 			left_max = sum;
// 	}

// 	sum = 0;
// 	int right_max = INT_MIN;
// 	for (int i = center + 1; i <= right; ++i)
// 	{
// 		sum += a[i];
// 		if (sum > right_max)
// 			right_max = sum;
// 	}
// 	int ret = left_max + right_max;
// 	ret = ret < leftMaxInterval ? leftMaxInterval : ret;
// 	ret = ret < rightMaxInterval ? rightMaxInterval : ret;
// 	return ret;
// }

// int main(int argc, char const *argv[])
// {
// 	int a[] = {0, -3, -4, -5, -10, -3, -7, -2, -10, -2, -3};
// 	printf("%d\n", maxInterval(a, 1, 10));
// 	return 0;
// }

// Method_3

int maxSum(int * A, int n)
{
	int start[n];
	int all[n];
	start[n - 1] = A[n - 1];
	all[n - 1] = A[n - 1];
	for (int i = n - 2; i >= 0; --i)
	{
		start[i] = max(A[i], A[i] + start[i + 1]);
		all[i] = max(start[i], all[i + 1]);
	}
	return all[0];
}

int MaxSum(int * A, int n)
{
	int nStart = A[n - 1];
	int nAll = A[n - 1];
	for (int i = n - 2; i >= 0; --i)
	{
		if (nStart < 0)
			nStart = 0;
		nStart += A[i];
		if (nStart > nAll)
			nAll = nStart;
	}
	return nAll;
}

int main(int argc, char const *argv[])
{
	int a[] = {0, 3, -4, 5, 1, 3, -7, 2, 1, -2, 3};
	int n = 10;
	cout << MaxSum(a, n) << endl;
	// int max = INT_MIN;
	// int b[n + 1];
	// int start[n + 1];
	// int end = 0;
	// memset(b, 0, n + 1);
	// memset(start, 0, n + 1);
	// for (int i = 1; i <= n; ++i)
	// {
	// 	if (b[i - 1] > 0)
	// 	{
	// 		b[i] = b[i - 1] + a[i];
	// 		start[i] = start[i - 1];
	// 	}
	// 	else
	// 	{
	// 		b[i] = a[i];
	// 		start[i] = i;
	// 	}
	// 	if (b[i] > max)
	// 	{
	// 		max = b[i];
	// 		end = i;
	// 	}
	// }
	// printf("start: %d\nend  : %d\nmax  : %d\n", start[end], end, max);
	// return 0;
}

#include <iostream>
#include <cstring>

using namespace std;


int * father; // Union-Fund
// Used to determine if there is only one connected path
int * node_num;


int get(int x)
{
	return father[x] == x ? x : father[x] = get(father[x]);
}


int main(int argc, char const *argv[])
{
	int N, M, node_1, node_2, v, i;
	cin >> N >> M;
	if (N < 1)
	{
		printf("0\n");
		return 0;
	}
	if (N < 2)
	{
		printf("1\n");
		return 0;
	}
	father = new int[N + 1];
	node_num = new int[N + 1];
	for (i = 1; i <= N; i++)
		father[i] = i;
	memset(node_num, 0, (N + 1) * sizeof(int));
	for (i = 0; i < M; i++)
	{
		cin >> node_1 >> node_2;
		father[get(node_2)] = get(node_1);
		node_num[node_1]++;
		node_num[node_2]++;
	}
	v = get(1);
	for (i = 2; i <= N; i++)
	{
		if (v != get(i))
		{
			printf("0\n");
			return 0;
		}
	}
	for (i = 1; i <= N; i++)
	{
		if (node_num[i] % 2 == 1)
		{
			printf("0\n");
			return 0;
		}
	}
	printf("1\n");
	delete father;
	delete node_num;
	return 0;
}

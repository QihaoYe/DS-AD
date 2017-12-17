#include <iostream>
#define BOUNDARY_X 50
#define BOUNDARY_Y 50


// bfs
using namespace std;
int main(int argc, char const *argv[])
{
	
	return 0;
}


void DFS(int V)
{
    Visited[V] = true;
    printf("%d ", V);
    for (int i = 0; i < n; i++)
    {
        if (G[V][i] && !Visited[i])
            DFS(i);
    }
}

void BFS(int V)
{
    const int MAX_SIZE = 100;
    int Queue[MAX_SIZE];
    int first = -1, last = -1;

    Queue[++last] = V;      //入队
    Visited[V] = true;
    while (first < last)    //当队不为空时
    {
        int F = Queue[++first];     //出队
        printf("%d ", F);
        for (int i = 0; i < n; i++)
        {
            if (G[F][i] && !Visited[i])
            {
                Queue[++last] = i;      //入队
                Visited[i] = true;
            }
        }
    }
}

void InitVisit()
{
    for (int i = 0; i < N; i++)
        Visited[i] = false;
}

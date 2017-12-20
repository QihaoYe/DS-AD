#include <iostream>
#define MAX_LENGTH 64
#define FatalError(code) fprintf(stderr, code)
#define BOUNDARY_X 50
#define BOUNDARY_Y 50
#define LEAP 5
#define POINT_NUMBER 300
using namespace std;


typedef struct point
{
    int x;
    int y;
    point()
    {
        this->x = 0;
        this->y = 0;
    }
    point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

}point;


int distance_square(point a1, point a2)
{
    return (a1.x - a2.x) * (a1.x - a2.x) + (a1.y - a2.y) * (a1.y - a2.y);
}

int is_near_boundary(point a)
{
    if (abs(a.x - BOUNDARY_X) <= LEAP || abs(a.x + BOUNDARY_X) <= LEAP)
        return 1;
    if (abs(a.y - BOUNDARY_Y) <= LEAP || abs(a.y + BOUNDARY_Y) <= LEAP)
        return 1;
    return 0;
}


void read_in(FILE ** fp, const char * PATH, char * filename)
{
    char document[5 * MAX_LENGTH];
    strcpy(document, PATH);
    for (int i=(int)strlen(document) - 1; i >= 0; i--)
    {
        if (document[i] == '/')
            break;
        document[i] = '\0';
    }
    strcat(document, filename);
    if (NULL == (*fp = fopen(document,"r")))
        FatalError("Can not open the file!\n");
}
// Use the absolute path of the source document


int main(int argc, char const *argv[])
{
	FILE * fp;
    argv[0] = "/Users/apple/Documents/Data_Structures/12_01/12";
    char filename[] = "points.txt";
    read_in(&fp, argv[0], filename);
    point points[POINT_NUMBER];
    int adjacency_matrix[POINT_NUMBER][POINT_NUMBER];
    memset(adjacency_matrix, 0, sizeof(adjacency_matrix));
    int index = 0;
    int LEAP_SQUARE = LEAP * LEAP;
    while (!feof(fp))
    {
        int x, y, flag;
        flag = fscanf(fp, "%d %d", &x, &y);
        if (flag != 2)
            break;
        points[index].x = x;
        points[index].y = y;
        index++;
    }
    for (int i = 0; i < POINT_NUMBER; i++)
    {
        for (int j = i + 1; j < POINT_NUMBER; j++)
            if (distance_square(points[i], points[j]) <= LEAP_SQUARE)
                adjacency_matrix[i][j] = adjacency_matrix[j][i] = 1;
        if (is_near_boundary(points[i]))
            adjacency_matrix[i][i] = 2;
    }
    for (int i = 0; i < POINT_NUMBER; i++)
    {
        for (int j = 0; j < POINT_NUMBER; j++)
        {
            cout << adjacency_matrix[i][j] << " ";
        }
        cout << endl;
    }
	return 0;
}


//void DFS(int V)
//{
//    Visited[V] = true;
//    printf("%d ", V);
//    for (int i = 0; i < n; i++)
//    {
//        if (G[V][i] && !Visited[i])
//            DFS(i);
//    }
//}
//
//void BFS(int V)
//{
//    const int MAX_SIZE = 100;
//    int Queue[MAX_SIZE];
//    int first = -1, last = -1;
//
//    Queue[++last] = V;      //入队
//    Visited[V] = true;
//    while (first < last)    //当队不为空时
//    {
//        int F = Queue[++first];     //出队
//        printf("%d ", F);
//        for (int i = 0; i < n; i++)
//        {
//            if (G[F][i] && !Visited[i])
//            {
//                Queue[++last] = i;      //入队
//                Visited[i] = true;
//            }
//        }
//    }
//}
//
//void InitVisit()
//{
//    for (int i = 0; i < N; i++)
//        Visited[i] = false;
//}

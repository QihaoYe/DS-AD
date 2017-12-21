#include <iostream>
#define MAX_LENGTH 64
#define FatalError(code) fprintf(stderr, code)
#define BOUNDARY_X 50
#define BOUNDARY_Y 50
#define LEAP 5
#define POINT_NUMBER 500
using namespace std;


typedef struct point
{
    int x;
    int y;
    int previous;
    point()
    {
        this->x = 0;
        this->y = 0;
        this->previous = -1;
    }
    point(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->previous = -1;
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


void BFS(int point_num);
point points[POINT_NUMBER + 1];
int adjacency_matrix[POINT_NUMBER + 1][POINT_NUMBER + 1];


int main(int argc, char const *argv[])
{
	FILE * fp;
    char filename[] = "points.txt";
    read_in(&fp, argv[0], filename);
    memset(adjacency_matrix, 0, sizeof(adjacency_matrix));
    points[0] = point(0, 0);
    int index = 1;
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
    for (int i = 0; i <= POINT_NUMBER; i++)
    {
        for (int j = i + 1; j <= POINT_NUMBER; j++)
            if (distance_square(points[i], points[j]) <= LEAP_SQUARE)
                adjacency_matrix[i][j] = adjacency_matrix[j][i] = 1;
        if (is_near_boundary(points[i]))
            adjacency_matrix[i][i] = 2;
    }
    BFS(0);
	return 0;
}

void BFS(const int point_num)
{
    int queue[POINT_NUMBER + 1];
    int visited[POINT_NUMBER + 1];
    memset(visited, 0, sizeof(visited));
    int first = -1, last = -1;
    int result[POINT_NUMBER + 1];
    // Store the path
    int index = -1;
    queue[++last] = point_num;
    visited[point_num] = 1;
    while (first < last)
    {
        int F = queue[++first];
        if (adjacency_matrix[F][F] == 2)
        {
            point temp = points[F];
            result[++index] = F;
            while (temp.previous != -1)
            {
                result[++index] = temp.previous;
                temp = points[temp.previous];
            }
            break;
        }
        for (int i = 0; i <= POINT_NUMBER; i++)
        {
            if (adjacency_matrix[F][i] && !visited[i])
            {
                queue[++last] = i;
                visited[i] = 1;
                points[i].previous = F;
            }
        }
    }
    index++;
    while (index-- > 0)
        cout << points[result[index]].x << " " << points[result[index]].y << endl;
}

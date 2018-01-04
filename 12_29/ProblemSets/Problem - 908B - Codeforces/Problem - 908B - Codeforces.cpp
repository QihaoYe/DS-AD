#include <iostream>
#include <algorithm>
#include <string.h>


using namespace std;
int is_valid(char ** maze, int x, int y, int m, int n)
{
    if (x < 0 || x >= m)
        return 0;
    if (y < 0 || y >= n)
        return 0;
    switch (maze[y][x])
    {
        case '.':
        case 'S':return 1;
        case 'E':return 2;
        default:return 0;
    }
}


int main(int argc, char const *argv[])
{
    int instruction[] = {3, 2, 1, 0};
    int move[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0 ,-1}};
    int n, m, _, __, sx, sy, count = 0;
    cin >> n >> m;
    char ** maze = new char*[n];
    for (_ = 0; _ < n; _++)
    {
        maze[_] = new char[m];
        for (__ = 0; __ < m; __++)
        {
            cin >> maze[_][__];
            if (maze[_][__] == 'S')
            {
                sx = __;
                sy = _;
            }
        }
    }
    char instructions[100];
    cin >> instructions;
    int l = (int)strlen(instructions);
    for (int i = 0; i < 24; i++)
    {
        int x = sx, y = sy, flag;
        next_permutation(instruction, instruction + 4);
        for (_ = 0; _ < l; _++)
        {
            y += move[instruction[instructions[_] - '0']][0];
            x += move[instruction[instructions[_] - '0']][1];
            flag = is_valid(maze, x, y, m, n);
            if (flag == 1)
                continue;
            else if (flag == 2)
            {
                count++;
                break;
            }
            else
                break;
        }
    }
    cout << count << endl;
    return 0;
}

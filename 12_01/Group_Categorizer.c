#include <stdio.h>
#include <math.h>
#include <string.h>
#define N 5
#define M 5


int peoples[M][N] = {
                     { 30,   0,  40,  40,   0},
                     { 60,   1,  80,  80,   1},
                     {  0,  50,   1,   1,  60},
                     {  1, 100,   2,   3, 120},
                     {  2, 200,   4,   5, 230}
                    };
int balance[] = {1, 1, 1, 1, 1};
// Used to get threshold


double norm(const int * p, int n)
{
    int norm = 0;
    for (int i = 0; i < n; i++)
        norm += p[i] * p[i];
    return sqrt(norm);
}


double similarity(int * p1, int * p2, int n)
{
    double cos = 0.0;
    for (int i = 0; i < n; i++)
        cos += p1[i] * p2[i];
    cos /= (norm(p1, n) * norm(p2, n));
    return cos;
}


void categorize(int * focus)
{
    printf("------------------------------\n");
    int classification[M];
    double THRESHOLD = similarity(focus, balance, 5);
    // Set threshold

    for (int i = 0; i < M; i++)
        classification[i] = similarity(focus, peoples[i], N) > THRESHOLD;
    printf("# of Interested Group:\n");
    for (int i = 0; i < M; i++)
        if (classification[i])
            printf("%3d ", i);
    printf("\n");
    printf("# of NOT Interested Group:\n");
    for (int i = 0; i < M; i++)
        if (!classification[i])
            printf("%3d ", i);
    printf("\n");
    printf("------------------------------\n");
}


int main(int argc, char const *argv[])
{
    int focus[N];
    printf("Military Websites:\n");
    memset(focus, 0, sizeof(focus));
    focus[0] = 1;
    // {1, 0, 0, 0, 0}
    categorize(focus);
    printf("Shopping Websites:\n");
    memset(focus, 0, sizeof(focus));
    focus[1] = 1;
    // {0, 1, 0, 0, 0}
    categorize(focus);
    printf("Automotive Websites:\n");
    memset(focus, 0, sizeof(focus));
    focus[2] = 1;
    // {0, 0, 1, 0, 0}
    categorize(focus);
    printf("Games Websites:\n");
    memset(focus, 0, sizeof(focus));
    focus[3] = 1;
    // {0, 0, 0, 1, 0}
    categorize(focus);
    printf("Group Buy Websites:\n");
    memset(focus, 0, sizeof(focus));
    focus[4] = 1;
    // {0, 0, 0, 0, 1}
    categorize(focus);
	return 0;
}
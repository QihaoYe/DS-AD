#include <iostream>


using namespace std;


int main(int argc, char const *argv[])
{
	int N = 100, i, j, local_maximum, maximum = 0;
    int A[N];
    srand((unsigned)time(NULL));
    for (i = 0; i < N; i++)
        A[i] = rand() % (10 * N);
    // Generate random array

    cout << "Origin array: " << endl;
    for (i = 0; i < N; i++)
        cout << A[i] << ' ';
    cout << endl;
    int dp[N + 1];
    memset(dp, 0, sizeof(dp));
    for (i = 1; i <= N; i++)
    {
        local_maximum = 0;
        for (j = 0; j < i - 1; j++)
            if (A[i - 1] > A[j] && dp[j + 1] > local_maximum)
                local_maximum = dp[j + 1];
        dp[i] = local_maximum + 1;
        if (dp[i] > maximum)
            maximum = dp[i];
    }
    // Get DP array and maximum length
    
    cout << "Longest Length\n= " << maximum << endl << "One of Longest Increasing Subsequence\n= ";
    j = maximum;
    i = N - 1;
    int* result = new int(maximum);
    while (j > 0)
    {
        if (dp[i + 1] == j)
        {
            result[j - 1] = A[i];
            j--;
        }
        i--;
    }
    // It should be increasing
    for (j = 0; j < maximum; j++)
        cout << result[j] << ' ';
    cout << endl;
    // Output the result
    delete result;
	return 0;
}
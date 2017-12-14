#include <iostream>


using namespace std;
int main(int argc, char const *argv[])
{
	char s_1[] = "jkgfkgfgjffdgd";
	char s_2[] = "andcasdkfnkasd";
	int n_1, n_2, i, j, k;
    n_1 = (int)strlen(s_1);
    n_2 = (int)strlen(s_2);
    // Get the length

    int dp[n_1 + 1][n_2 + 1];
    memset(dp, 0, sizeof(dp));
    // Initialization

    for (i = 1; i <= n_1; i++)
        for (j = 1; j <= n_2; j++)
        {
            if (s_1[i - 1] == s_2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
    // DP process

    i = n_1;
    j = n_2;
    k = dp[n_1][n_2];
    char * result = new char[k];
    while (k > 0)
    {
        if (s_1[i - 1] == s_2[j - 1])
        {
            result[k - 1] = s_1[i - 1];
            i--;
            j--;
            k--;
        }
        else if (dp[i - 1][j] == dp[i][j])
            i--;
        else
            j--;
    }
    cout << "Longest Length\n= " << dp[n_1][n_2] << endl << "One of Longest String\n= " << result << endl;
    // Output the result
    delete[] result;
	return 0;
}

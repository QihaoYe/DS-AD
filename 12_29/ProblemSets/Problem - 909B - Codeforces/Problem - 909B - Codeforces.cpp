#include <iostream>


using namespace std;
int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    if (n % 2)
    	cout << (n + 1) * (n + 1) / 4 << endl;
    else
    	cout << n * (n + 2) / 4 << endl;
    return 0;
}

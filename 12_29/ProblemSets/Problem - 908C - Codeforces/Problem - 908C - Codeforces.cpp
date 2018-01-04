#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;
int main(int argc, char const *argv[])
{
    int n, r, _, __;
    cin >> n >> r;
    int * x = new int[n];
    double * y = new double[n];
    for (_ = 0; _ < n; _++)
    {
        cin >> x[_];
        y[_] = (double)r;
        double temp;
        for (__ = 0; __ < _; __++)
            if (abs(x[_] - x[__]) <= 2 * r)
            {
                temp = y[__] + sqrt(4 * r * r - (x[_] - x[__]) * (x[_] - x[__]));
                if (temp > y[_])
                    y[_] = temp;
            }
        cout << setprecision(12) << y[_] << " ";
    }
    cout << endl;
    delete[] x;
    delete[] y;
    return 0;
}

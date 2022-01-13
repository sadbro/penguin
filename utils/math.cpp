#include <bits/stdc++.h>
#define pi 3.1415
using namespace std;

int factorial(int x)
{
    if (x == 0 || x == 1)
    {
        return 1;
    }

    return x * factorial(x - 1);
}
void cal_sin(float n)
{   
    float accuracy = 0.0001, denominator, sinx, sinval;
     
    // Converting degrees to radian
    n = n * (3.142 / 180.0);
 
    float x1 = n;
     
    // maps the sum along the series
    sinx = n;        
      
    int i = 1;
    do
    {
        denominator = 2 * i * (2 * i + 1);
        x1 = -x1 * n * n / denominator;
        sinx = sinx + x1;
        i = i + 1;
    } while (i<=100);
    cout << sinx;
}

int main()
{
    double aid;
    cin >> aid;
    // int sign = 1;
    // double air = aid * (pi / 180.0);
    // double res=0;
    // for (int i = 1; i <= 80; i = i + 2)
    // {
    //     res += sign * (pow(air, i) / factorial(i));

    //     sign *= -1;
    // }

    // cout << res;
    cal_sin(aid);

    return 0;
}

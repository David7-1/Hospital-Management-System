using namespace std;
#include<string>

#include "global.h"

int yyyymmdd;
int power(int n, int exp)
{
    int res = 1;
    while (exp != 0)
    {
        if (exp & 1)
            res *= n, exp--;
        else
            n *= n, exp >>= 1;
    }
    return res;
}
int strToNum(string s)
{
    int res = 0;
    for (int i = s.size()-1; i >= 0; i=i-1)
    {
        res = res + (s[i] - '0') * power(10, (s.size()-1-i));
    }
    return res;
}
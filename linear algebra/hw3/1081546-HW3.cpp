#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<iomanip>
using namespace std;
const int N = 4096;
const float PI = 3.1416;
inline void swap(float& a, float& b)
{
    float t;
    t = a;
    a = b;
    b = t;
}

void bitrp(float xreal[], float ximag[], int n)
{
    // 位反轉置換 Bit-reversal Permutation
    int i, j, a, b, p;

    for (i = 1, p = 0; i < n; i *= 2)
    {
        p++;
    }
    for (i = 0; i < n; i++)
    {
        a = i;
        b = 0;
        for (j = 0; j < p; j++)
        {
            b = (b << 1) + (a & 1);     // b = b * 2 + a % 2;
            a >>= 1;         // a = a / 2;
        }
        if (b > i)
        {
            swap(xreal[i], xreal[b]);
            swap(ximag[i], ximag[b]);
        }
    }
}

void FFT(float xreal[], float ximag[], int n)
{
    // 快速傅立葉變換，將復數 x 變換后仍保存在 x 中，xreal, ximag 分別是 x 的實部和虛部
    float wreal[N / 2], wimag[N / 2], treal, timag, ureal, uimag, arg;
    int m, k, j, t, index1, index2;

    bitrp(xreal, ximag, n);

    // 計算 1 的前 n / 2 個 n 次方根的共軛復數 W'j = wreal [j] + i * wimag [j] , j = 0, 1,   , n / 2 - 1
    arg = -2 * PI / n;
    treal = cos(arg);
    timag = sin(arg);
    wreal[0] = 1.0;
    wimag[0] = 0.0;
    for (j = 1; j < n / 2; j++)
    {
        wreal[j] = wreal[j - 1] * treal - wimag[j - 1] * timag;
        wimag[j] = wreal[j - 1] * timag + wimag[j - 1] * treal;
    }

    for (m = 2; m <= n; m *= 2)
    {
        for (k = 0; k < n; k += m)
        {
            for (j = 0; j < m / 2; j++)
            {
                index1 = k + j;
                index2 = index1 + m / 2;
                t = n * j / m;     // 旋轉因子 w 的實部在 wreal [] 中的下標為 t
                treal = wreal[t] * xreal[index2] - wimag[t] * ximag[index2];
                timag = wreal[t] * ximag[index2] + wimag[t] * xreal[index2];
                ureal = xreal[index1];
                uimag = ximag[index1];
                xreal[index1] = ureal + treal;
                ximag[index1] = uimag + timag;
                xreal[index2] = ureal - treal;
                ximag[index2] = uimag - timag;
            }
        }
    }
}


int main(int argc, char* argv[])
{
    ifstream inFile(argv[1], ios::in);
    vector<vector<float>> vv;

    string s1, s2;
    float p;
    while (inFile >> s1)
    {
        vector<float> v;
        stringstream ss1;
        ss1 << s1;
        while (getline(ss1, s2, ','))
        {
            stringstream ss2;
            ss2 << s2;
            ss2 >> p;
            v.push_back(p);
        }
        vv.push_back(v);
    }

    int data = 0;
    for (int i = 0; i < vv.size(); ++i)
    {
        cout << "Data " << ++data << " :\n";
        float xreal[N] = {}, ximag[N] = {};
        for (int j = 0; j < vv[i].size(); ++j)
            xreal[j] = vv[i][j];
        FFT(xreal, ximag, vv[i].size());
        for (int j = 0; j < vv[i].size(); ++j)
            cout << setprecision(4) << fixed << xreal[j] << " " << ximag[j] << '\n';
        if (i < vv.size() - 1) cout << '\n';
    }

    return 0;
}
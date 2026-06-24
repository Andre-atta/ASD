//
// Created by Andrea on 17/04/2026.
//

#ifndef ASD_QUICKSORT_H
#define ASD_QUICKSORT_H
#include <vector>

using namespace std;

inline void scambia(int& a, int& b)
{
    const int temp {a};
    a = b;
    b = temp;
}

inline int partiziona(vector<int>& v, int p, int r)
{
    int x = v[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (v[j] <= x)
        {
            i++;
            scambia(v[i], v[j]);
        }
    }
    scambia(v[i + 1], v[r]);
    return i + 1;
}

inline void quickSort(vector<int>& v, int p, int r)
{
    if (p < r)
    {
        int q = partiziona(v, p, r);
        quickSort(v, p, q - 1);
        quickSort(v, q + 1, r);
    }
}

inline void quickSortWrapper(vector<int>& v)
{
    quickSort(v, 0, v.size() - 1);
}

#endif //ASD_QUICKSORT_H

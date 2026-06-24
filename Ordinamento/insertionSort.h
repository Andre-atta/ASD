//
// Created by Andrea on 13/04/2026.
//

#ifndef ASD_INSERTIONSORT_H
#define ASD_INSERTIONSORT_H
#include <vector> // Cambiato da #import a #include

using namespace std;


/**
 *  
 *
 */
inline void insertionSort(vector<int>& v)
{
    if (v.empty()) return;

    // Le posizioni partono da 0, quindi il ciclo parte da 1 (che è il secondo elemento, come j=2 nel pseudocodice)
    for (int j = 1; j < v.size(); j++)
    {
        const int key = v[j];
        int i = j - 1;


        while (i >= 0 && key < v[i])
        {
            v[i + 1] = v[i];
            i -= 1;
        }
        v[i + 1] = key;
    }
}

#endif //ASD_INSERTIONSORT_H

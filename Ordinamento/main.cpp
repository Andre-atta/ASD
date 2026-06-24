//
// Created by Andrea on 13/04/2026.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "insertionSort.h"
#include "mergeSort.h"
#include "quickSort.h"

using namespace std;
using namespace std::chrono;

// Genera un array di dimensione 'size' con numeri casuali
vector<int> generateRandomVector(int size) {
    vector<int> v(size);
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 10000);

    for (int i = 0; i < size; ++i) {
        v[i] = dist(gen);
    }
    return v;
}

// Funzione template per misurare e stampare il tempo di elaborazione
template <typename Func>
void measureTime(const string& algorithmName, Func sortFunction, vector<int> v) {
    cout << "Avvio test per: " << algorithmName << "...\n";


    auto start = high_resolution_clock::now();
    sortFunction(v);
    auto end = high_resolution_clock::now();

    duration<double, milli> msDouble = end - start;
    cout << "  -> [TEMPO]: " << msDouble.count() << " ms\n\n";
}

int main() {
    int testSize = 1000;
    cout << "Generazione array di " << testSize << " elementi...\n\n";
    vector<int> randomArray = generateRandomVector(testSize);
    vector<int> arrayOn(testSize);
    vector<int> arrayOn2(testSize);

    for (int i = 0; i < testSize; ++i) {
        arrayOn[i] = i;                   // Array già ordinato (crescente)
        arrayOn2[i] = testSize - i;       // Array ordinato al contrario (decrescente)
    }

    measureTime("Insertion Sort O(n) [GIA' ORDINATO]", insertionSort, arrayOn);
    measureTime("Insertion Sort [CASO MEDIO]", insertionSort, randomArray);
    measureTime("Insertion Sort O(n2) [DECRESCENTE]", insertionSort, arrayOn2);

    measureTime("Merge Sort [CASO MEDIO]", mergeSortWrapper, randomArray);

    measureTime("Quick Sort [CASO MEDIO]", quickSortWrapper, randomArray);

    return 0;
}

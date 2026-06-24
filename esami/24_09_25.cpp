// Dato un vettore A di interi scrivere un algoritmo efficiente per trovare la “moda” degli elementi contenuti in A
// (ovvero il valore che compare più spesso). Nel caso di più valori che possono essere definiti come moda, ritornare
// il valore numericamente più alto.
// Si determini e giustifichi la complessità della funzione.

// Ad esempio, nel seguente vettore la moda è 30:
// 2  3  8  14  4  7  8  20  30  12  30  12  14  14  15  4  6  9  10  3  40  30

#include "iostream"
#include "vector"
#include "unordered_map"

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back
    // into arr[left..right]
    while (i < n1 && j < n2) { // O(n) di fatto scorriamo tutto l'array
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right){
    if (left >= right) return;

    int mid = left + (right - left)/2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int moda(vector<int> v)
{
    if (v.empty()) return 0; // Gestione caso base

    int max{v[0]}, cnt {1}, cnt_max{0};

    mergeSort(v, 0, v.size() -1);

    for (int i {1}; i < v.size(); i++)
    {
        if (v[i] == v[i-1])
            cnt++;
        else
        {
            if (cnt >= cnt_max)
            {
                cnt_max = cnt;
                max = v[i-1];
            }
            cnt = 1;
        }
    }
    if (cnt >= cnt_max)
        max = v[v.size() - 1];

    return max;
}

/**
 * La funzione moda scorre il vettore ordinato una sola volta, pertanto possiamo dire che la sua complessità temporale sarà O(n) dipendente dagli elementi dell'array.
 * Le operazioni al suo interno, come dichiarazione di variabili o if ed else sono tutte costanti e istantanee quindi trascurabili O(1).
 *
 * L'algoritmo è dominato dal merge sort, che ordina l'array di prezzi.
 * Analizziamo la sua complessità utilizzando il Teorema di Master.
 *
 * Il merge sort segue la ricorrenza:
 * T(n) = 2T(n/2) + Θ(n)
 *
 * Confrontiamo i parametri con il Teorema di Master:
 * - a = 2
 * - b = 2
 * - f(n) = Θ(n)
 *
 * Calcolo d:
 * d = log_b(a) = log_2(2) = 1
 *
 *Confronto f(n) con Θ(n^d):
 * - f(n) = Θ(n)
 * - n^d = n^1 = Θ(n)
 *
 * Siamo quindi nel Caso 2 del Teorema di Master, che si applica quando f(n) = Θ(n^d).
 * Di conseguenza, la complessità complessiva è:
 *
 * T(n) = Θ(n log n)
 *
 * Essendo il merge sort l'operazione più costosa dell'algoritmo, ne determina la classe asintotica finale.
 * Il resto dell'algoritmo (la ricerca delle coppie di libri) ha complessità O(n), che è inferiore a Θ(n log n) e quindi trascurabile nel computo finale.
 */


int moda_hash(const vector<int>& v) {
    if (v.empty()) return 0; // Gestione caso base

    unordered_map<int, int> frequenze;
    int max_valore = v[0];
    int max_cnt = 0;

    for (int num : v) {
        frequenze[num]++; // Inserisce o incrementa il contatore in O(1) medio

        if (frequenze[num] > max_cnt) {
            max_cnt = frequenze[num];
            max_valore = num;
        } else if (frequenze[num] == max_cnt) {
            // Gestione dello spareggio: a parità di occorrenze, vince il valore più alto
            if (num > max_valore) {
                max_valore = num;
            }
        }
    }

    return max_valore;
}

/**
 * ANALISI COMPLESSITÀ FUNZIONE moda_hash (Implementazione con Hash Map)
 * * COMPLESSITÀ TEMPORALE:
 * L'algoritmo esegue un singolo ciclo for che itera su tutti gli n elementi del vettore.
 * All'interno del ciclo, l'operazione dominante è l'inserimento/aggiornamento nella
 * tabella hash (std::unordered_map).
 * * In C++, unordered_map è implementata come una hash table, le cui operazioni di
 * inserimento e ricerca hanno un costo ammortizzato medio di O(1).
 * Le operazioni di confronto (if/else) avvengono in tempo costante O(1).
 * * Poiché eseguiamo n operazioni di costo medio O(1), la complessità temporale
 * media complessiva dell'algoritmo è lineare: O(n).
 * (Nota: nel caso pessimo assoluto, a causa di potenziali collisioni nell'hashing,
 * l'inserimento potrebbe degradare a O(n), portando la complessità a O(n^2), ma
 * questo evento è statisticamente trascurabile con buone funzioni di hash).
 */
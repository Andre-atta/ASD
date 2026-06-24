// Dato un albero binario i cui nodi x hanno i campi left, right e key, dove key è un numero intero:
//      a. definire l’altezza di un nodo x;
//      b. scrivere una funzione efficiente in C o C++ che ritorna il numero di nodi per i quali la chiave x->key è minore o uguale dell’altezza del nodo.
//      c. valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza e mostrando la loro risoluzione;

// 1 voglio restituire un conteggio
// 2 voglio le info dal nodo corrente e quindi pre order + contributo
// 3 caso base -> una volta che raggiungo le foglie
// 4 alla fine sommo


#include "../Alberi/alberiBinari.h"


#include <iostream>
#include <algorithm> // Per std::max

// Funzione ausiliaria che implementa il Pattern 1 (Post-order)
// RITORNA: l'altezza del nodo 'r'
// MODIFICA: la variabile 'cnt' passata per riferimento
int lessHeight_aux(Pnode r, int &cnt)
{
    // 3. Caso base
    // Se il nodo è vuoto, la sua altezza convenzionale è -1
    if (r == nullptr) return -1;

    // PATTERN 1: Post-order puro. Prima scendo fino in fondo.
    // Chiedo ai miei figli: "Qual è la vostra altezza?"
    int h_sx = lessHeight_aux(r->sx, cnt);
    int h_dx = lessHeight_aux(r->dx, cnt);

    // Ora che i figli mi hanno risposto, calcolo la MIA altezza
    int h_corrente = 1 + std::max(h_sx, h_dx);

    // 2. Contributo del nodo corrente
    // Ora ho la mia altezza. Posso fare il controllo richiesto!
    if (r->val <= h_corrente) {
        cnt++; // Trovato! Incremento il contatore condiviso
    }

    // 4. Ritorno l'info al genitore
    // Il mio genitore ha bisogno della mia altezza per calcolare la sua,
    // quindi gliela ritorno.
    return h_corrente;
}


// Funzione wrapper
int lessHeight(Pnode r)
{
    // 1. Creo una "scatola" vuota per tenere il conto
    int conteggio_totale = 0;

    // 2. Lancio l'esplorazione.
    // NOTA BENE: NON c'è scritto "return lessHeight_aux(...)".
    // Chiamo la funzione e IGNORO il suo valore di ritorno (l'altezza della radice).
    lessHeight_aux(r, conteggio_totale);

    // 3. Ora che l'esplorazione ha finito di aggiornare la scatola,
    // restituisco la scatola al professore!
    return conteggio_totale;
}

int main() {
    std::cout << "=== START TEST ALBERI BINARI ===" << std::endl;

    /*
     * Costruiamo il seguente albero di test per verificare i casi limite:
     *
     * (Radice: val=1) [Altezza = 2] -> 1 <= 2? SÌ (cnt++)
     * /        \
     * (n1: val=0)   (n2: val=3) [Altezza = 0] -> 3 <= 0? NO
     * [Altezza=1]
     * /     \
     * (n3: val=2) (n4: val=0) [Altezza = 0] -> 0 <= 0? SÌ (cnt++)
     * [Altezza=0]
     * 2 <= 0? NO
     *
     * Nodi che devono soddisfare la condizione (val <= altezza):
     * - n4 (val 0, h 0) -> SÌ
     * - n1 (val 0, h 1) -> SÌ
     * - Radice (val 1, h 2) -> SÌ
     *
     * Conteggio totale atteso: 3
     */

    // 1. Inizializzazione dell'albero con il valore della radice
    alberoBinario albero(1);
    Pnode root = albero.getRoot();

    // 2. Inserimento dei figli di primo livello
    // insert(padre, valore, asLeft) restituisce il puntatore al nodo creato
    Pnode n1 = albero.insert(root, 0, true);  // Figlio sinistro della radice
    Pnode n2 = albero.insert(root, 3, false); // Figlio destro della radice

    // 3. Inserimento dei figli di secondo livello (sotto n1)
    Pnode n3 = albero.insert(n1, 2, true);    // Figlio sinistro di n1
    Pnode n4 = albero.insert(n1, 0, false);   // Figlio destro di n1

    std::cout << "[INFO] Albero di test creato correttamente." << std::endl;

    // 4. Esecuzione del test
    int risultato_ottenuto = lessHeight(root);
    int risultato_atteso = 3;

    // 5. Verifica del risultato
    std::cout << "\n--- RISULTATI VALUTAZIONE ---" << std::endl;
    std::cout << "Conteggio atteso: " << risultato_atteso << std::endl;
    std::cout << "Conteggio ottenuto: " << risultato_ottenuto << std::endl;

    if (risultato_ottenuto == risultato_atteso) {
        std::cout << "\n[ESITO] TEST SUPERATO CON SUCCESSO! O(N) confermato." << std::endl;
    } else {
        std::cout << "\n[ESITO] ERRORE! Il conteggio non corrisponde." << std::endl;
    }

    return 0;
}
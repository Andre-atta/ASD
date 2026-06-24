#include <iostream>

using namespace std;

// Definizione della struttura del nodo come da consegna
struct Node {
    int key;
    Node* p;      // Puntatore al padre
    Node* left;   // Puntatore al figlio sinistro
    Node* right;  // Puntatore al figlio destro

    // Costruttore per comodità
    Node(int k) : key(k), p(nullptr), left(nullptr), right(nullptr) {}
};

// Definizione dei tipi richiesti
typedef Node* PNode;
typedef PNode PTree;

// Si scriva una funzione efficiente in C o C++ che restituisca una chiave che occorre
// il massimo numero di volte in T. Il prototipo della funzione è:
int maxOcc_aux(PNode r, int &prevKey, int &current_count, int &max_occ, int &max_key)
{
    if (!r) return 0;

    maxOcc_aux(r->left, r->p->key, current_count, max_occ, max_key);
    if (prevKey == r->key) current_count++;
    maxOcc_aux(r->right, r->p->key, current_count, max_occ, max_key);

    if (current_count >= max_occ)
    {
        max_occ = current_count;
        max_key = r->key;
    }
    return max_key;
}

int maxOcc(PTree t)
{
    if (!t) return 0;
    int prevKey = 0;
    int current_count = 1;
    int max_occ = current_count;
    int max_key = t->key;
    return maxOcc_aux(t->left, prevKey, current_count, max_occ, max_key);
}


// ====================================================================
// FUNZIONI DI UTILITÀ (Non fanno parte dell'esame ma servono per testare)
// ====================================================================

// Funzione per inserire un nodo in un BST (gestisce anche i duplicati)
// In questa implementazione, le chiavi >= alla radice vanno a destra.
PTree insertBST(PTree root, int key) {
    PNode z = new Node(key);
    PNode y = nullptr;
    PNode x = root;

    while (x != nullptr) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            // I duplicati o i valori maggiori vanno nel sottoalbero destro
            x = x->right;
        }
    }
    
    z->p = y; // Imposto il puntatore al padre
    
    if (y == nullptr) {
        root = z; // L'albero era vuoto
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    return root;
}

// Funzione per stampare l'albero in ordine (In-Order Traversal)
// In un BST, stampa i valori in ordine crescente.
void printInOrder(PTree t) {
    if (t != nullptr) {
        printInOrder(t->left);
        cout << t->key << " ";
        printInOrder(t->right);
    }
}

// ====================================================================
// MAIN DI TEST
// ====================================================================
int main() {
    PTree root = nullptr;

    // Creiamo un albero di test con le seguenti chiavi:
    // 10, 5, 15, 5, 20, 5, 10
    // Il numero 5 compare 3 volte (massimo numero di occorrenze)
    // Il numero 10 compare 2 volte
    // Gli altri 1 volta
    
    root = insertBST(root, 10);
    root = insertBST(root, 15);
    root = insertBST(root, 15);
    root = insertBST(root, 15);
    root = insertBST(root, 20);
    root = insertBST(root, 5);
    root = insertBST(root, 10);

    cout << "Contenuto dell'albero (In-Order): ";
    printInOrder(root);
    cout << endl;

    // Testiamo la funzione
    int result = maxOcc(root);
    
    cout << "La chiave con il massimo numero di occorrenze e': " << result << endl;
    cout << "Risultato atteso: 5" << endl;

    return 0;
}
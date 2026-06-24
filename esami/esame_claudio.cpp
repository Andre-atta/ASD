#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};
typedef Node* PNode;
// Scrivi una funzione efficiente in C++ che restituisce la somma delle chiavi dei nodi foglia dell'albero.
// Cosa restituisco? -> somma
// Ho bisogno di info dai figli o dal genitore? -> dai figli
// Qual è il caso base? r -> nullptr
// Come combino i risultati? -> sommo valori trovati


// --- FIRMA DA ESAME ---
// la complessità è data dalle ricorrenze della funzione stessa, T(k) + T(n-k-1) + d che poi diventa O(n)
int sumLeaves(PNode r)
{

    if (!r) return 0;
    if (!r->left && !r->right)
        return r->key;

    int fsx = sumLeaves(r->left);
    int fdx = sumLeaves(r->right);

    return fsx + fdx;
}


// --- MAIN DI TEST --
int main() {
    /*
         10
        /  \
       5    3
      / \    \
     2   7    8
    */
    PNode root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(3);
    root->left->left = new Node(2);
    root->left->right = new Node(7);
    root->right->right = new Node(8);

    // Foglie: 2, 7, 8 → somma attesa = 17
    cout << "Somma foglie: " << sumLeaves(root) << endl;
    cout << "Atteso: 17" << endl;

    // Caso base: albero con un solo nodo (la radice e anche foglia)
    PNode single = new Node(42);
    cout << "Nodo singolo: " << sumLeaves(single) << endl;
    cout << "Atteso: 42" << endl;

    // Albero vuoto
    cout << "Albero vuoto: " << sumLeaves(nullptr) << endl;
    cout << "Atteso: 0" << endl;

    return 0;
}
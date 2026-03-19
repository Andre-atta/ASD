//
// Created by Andrea on 16/03/2026.
//

#ifndef ASD_ALBERIBINARI_H
#define ASD_ALBERIBINARI_H

#include "vector"
using namespace std;

struct Node
{
    int val;
    Node* sx;
    Node* dx;
    Node(int v) : val(v), sx(nullptr), dx(nullptr) {}
};
typedef Node* Pnode;

class alberoBinario
{
    Pnode root;

    static void deleteRec(Pnode n)
    {
        if (!n) return;
        deleteRec(n->sx);
        deleteRec(n->dx);
        delete n;
    }

    Pnode padreRec(Pnode curr, Pnode target) const
    {
        if (!curr) return nullptr; // O(1)
        if (curr->sx == target || curr->dx == target) return curr;   // O(1)

        // ricorsione su sottoalbero sx
        Pnode risultato = padreRec(curr->sx, target); // O(n)
        if (risultato) return risultato; // O(1)

        // ricorsione sottoalbero dx
        return padreRec(curr->dx, target); // O(n)
    }


public:
    // newtree () -> Tree
    alberoBinario() : root(nullptr) {}
    ~alberoBinario()
    {
        deleteRec(root);
    }

    /** COSTO OPERAIONE:
     * * tempo costante, guardo sempre e solo un elemento
     */
    bool treeEmpty() const
    {
        return root == nullptr;
    }

    /** COSTO OPERAIONE:
     * * O(n)
     */
    Pnode padre(Pnode v) const
    {
        if (treeEmpty() || v == root) return nullptr;
        return padreRec(root, v);
    }

    /** COSTO OPERAZIONE:
     * * O(1) le operazioni sui vector sono costanti
     */
    vector<Pnode> figli (Pnode v)
    {
        vector<Pnode> listaFigli;
        if (v->sx) listaFigli.push_back(v->sx);
        if (v->dx) listaFigli.push_back(v->dx);

        return listaFigli;
    }


};




#endif //ASD_ALBERIBINARI_H
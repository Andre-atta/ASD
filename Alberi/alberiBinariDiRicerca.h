//
// Created by Andrea on 03/04/2026.
//

#ifndef ASD_ALBERIBINARIDIRICERCA_H
#define ASD_ALBERIBINARIDIRICERCA_H
#include "alberiBinari.h"


class alberoRicercato : public alberoBinario
{
public:
    alberoRicercato() = default;

    alberoRicercato(int val) : alberoBinario(val)
    {
    }

    alberoRicercato(const alberoRicercato& other) : alberoBinario(other)
    {
    }

    /**
     * il for-each scorre per definizione tutti gli elementi dell'array dunque è O(n)
     * senza possibilità di miglioramento.
     * Inoltre tree_insert sappiamo avere un tempo pari a O(h) che nel caso peggiore
     * è O(n) dunque per questo il risultato della complessità della insert è O(n^2)
     */
    void buildBST(vector<int>& elemList)
    {
        if (elemList.empty()) return;

        for (auto e : elemList) // O(n)
        {
            auto newNode = new Node(e);
            tree_insert(newNode); // O(h)
        }
    }

    /**
     * Osservando il codice notiamo che possiamo applicare il teorema master, procediamo calcolando le variabili:
     * a = 1 & b = 2
     * f(n) = O(1)
     *
     * CALCOLIAMO
     * d = log_b(a) = 0
     * e ricaviamo g(n^d) => g(n) = O(1)
     *
     * Siamo nel secondo caso perchè f(n) = g(n)
     *
     * dunque T(n) = O(n^d log(n)) => T(n) = log(n)
     *
     */
    Pnode tree_serch(Pnode x, int k)
    {
        if (!x || x->val == k) return x; // O(1)
        return (x->val > k) ? tree_serch(x->sx, k) : tree_serch(x->dx, k); // T(n/2)
    }

    /**
     * Il tempo di esecuzione è O(h) perché, come in Tree_search(), la sequenza dei nodi visitati forma
     * un cammino che scende dalla radice, e che può avere lunghezza massima h.
     *
     * Dove nel caso peggiore degenera a O(n), mentre il caso medio è O(log n)
     */
    Pnode tree_max(Pnode x)
    {
        if (!x) return nullptr;

        if (!x->dx) return x;
        return tree_max(x->dx); // T(n/2)
    }

    Pnode tree_min(Pnode x)
    {
        if (!x) return nullptr;

        if (!x->sx) return x;
        return tree_min(x->sx); // T(n/2)
    }

    Pnode tree_predecessor(Pnode x)
    {
        if (!x) return nullptr;

        if (x->sx) return tree_max(x->sx); // T(n/2)
        Pnode y = x->p;
        while (y != nullptr && x == y->sx)
        {
            // O(h)
            x = y;
            y = y->p;
        }
        return y;
    }

    Pnode tree_successor(Pnode x)
    {
        if (!x) return nullptr;

        if (x->dx) return tree_min(x->dx); // T(n/2)
        Pnode y = x->p;
        while (y != nullptr && x == y->dx)
        {
            // O(h)
            x = y;
            y = y->p;
        }
        return y;
    }

    /**
     * Il ciclo while costa O(h), e le altre istruzioni sono semplici assegnamenti:
     * il tempo di esecuzione è quindi O(h) perché si segue un cammino dalla radice verso il basso.
     */
    void tree_insert(Pnode z)
    {
        if (!z) return;
        if (!tree.root)
        {
            tree.root = z;
            return;
        }

        Pnode y{nullptr},
              x{tree.root};

        while (x != nullptr) // O(h)
        {
            y = x;
            if (z->val < x->val)
                x = x->sx;
            else
                x = x->dx;
        }

        z->p = y;

        if (z->val < y->val) y->sx = z;
        else y->dx = z;
    }

    /**
     * NB. transplant si occupa solo di inserire un novo nodo v al posto di u, aggiornando
     * solo il riferimento al padre, tutto il resto viene gestito nelle altre funzioni.
     * Il vantaggio è che questa operazione costa O(1) perchè son tutti semplici assegnamenti
     */
    void transplant(Pnode u, Pnode v)
    {
        if (!u->p) tree.root = v;
        else if (u == u->p->sx)
            u->p->sx = v;
        else
            u->p->dx = v;
        if (v)
            v->p = u->p;
    }

    /**
     * Da notare come la complessità dell'algoritmo sia data dalla ricerca del successore
     * che come tutte le ricerche dei BST impiega O(h)
     */
    void tree_delete(Pnode z)
    {
        if (!z->sx) { transplant(z, z->dx);
        }
        else if (!z->dx) { transplant(z, z->sx);
        } else {
            auto y = tree_successor(z); // O(h)
            if (y->p != z) {
                transplant(y, y->dx);
                y->dx = z->dx;
                z->dx->p = y;
            }
            transplant(z, y);
            y->sx = z->sx;
            y->sx->p = y;
        }
    }

    /**
     * ottimizziamo la funzione per creare un BST.
     * Come?
     * Mettiamo come precondizione che l'array debba essere ordinato, ma questa volta
     * partiamo dalla metà di questo e non dal primo elemento
     *
     * dopo di che procediamo a costruire il BST nello stesso modo sfruttato dal merge sort
     */
    alberoRicercato buildBSTott(vector<int>& v)
    {
        alberoRicercato t;
        t.tree.root = buildBSTottAux(v, 0, v.size() - 1, nullptr);
        return t;
    }

    /**
     * Possiamo calcolare la complessità sfruttando il teorema master infatti:
     * a = 2 | b = 2 => d = log_b(a) = 1
     * f(n) = d | g(n) = n
     *
     * Verifichiamo d'essere nel primo caso del Master Theorem
     * f(n) = O(n1−ε), ε >0. Se ε = 1 → n^1−ε = n^0 = 1;
     *
     * dunque T(n) = Θ(n).
     *
     * NB  Omega = d
     *     O = n
     */
    Pnode buildBSTottAux(vector<int>& v, int inf, int sup, Pnode padre)
    {
        if (inf > sup) return nullptr;

        int med{(inf + sup) / 2};
        auto r = new Node(v.at(med));
        r->p = padre;
        r->sx = buildBSTottAux(v, inf, med - 1, r); // T(n/2)
        r->dx = buildBSTottAux(v, med + 1, sup, r); // T(n/2)
        return r;
    }
};

#endif //ASD_ALBERIBINARIDIRICERCA_H

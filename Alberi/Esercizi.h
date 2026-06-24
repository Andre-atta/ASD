//
// Created by Andrea on 30/03/2026.
//

#ifndef ASD_ESERCIZI_H
#define ASD_ESERCIZI_H

#include "alberiBinari.h"
#include "alberiBinariDiRicerca.h"


/*
* Un nodo di un albero binario è detto centrale se il numero di foglie del sottoalbero
* di cui è radice è pari alla somma delle chiavi dei nodi appartenenti al
* cammino dalla radice al nodo stesso.
*
* a) Scrivere un algoritmo efficiente che restituisce il numero di nodi centrali.
*/

inline int nodo_centrale_aux(Pnode r, int sum, int& leaf)
{
    int nodoC, leafSx, leafDx;
    if (!r) {
        leaf = 0;
        return 0;
    }

    if (!r->sx && !r->dx)
    {
        leaf = 1;
        nodoC = 0;
    } else
    {
        int nodoSx = nodo_centrale_aux(r->sx, sum + r->val, leafSx);
        int nodoDx = nodo_centrale_aux(r->dx, sum + r->val, leafDx);
        leaf = leafSx + leafDx;
        nodoC = nodoDx + nodoSx;
    }

    return leaf == sum + r->val ? nodoC + 1 : nodoC;
}

inline int tre_bilanciato_aux(Pnode r, int& min, int& max)
{
    int minSx, maxSx, minDx, maxDx;
    if (!r) {
        min = -1;
        max = -1;
    } else {
        tre_bilanciato_aux(r->sx, minSx, maxSx);
        tre_bilanciato_aux(r->dx, minDx, maxDx);
        min = (minSx <= minDx ? minSx : minDx) + 1;
        max = (maxSx >= maxDx ? maxSx : maxDx) + 1;
    }
    return max - min;
}

/*
* Dato un albero binario di ricerca T, scrivere un algoritmo efficiente che sostituisca
* il numero di elementi che occorrono una sola volta e analizzarne la complessità.
*
*/
int contaDistinti(alberoRicercato& t)
{
    if (!t.getRoot()) return 0;
    int dist{0}, count{1};
    Pnode pc {t.tree_min(t.getRoot())};
    int val = pc->val;
    pc = t.tree_successor(pc);

    while (pc)
    {
        if (pc->val == val) count++;
        else {
            if (count == 1) dist++;
            count = 1;
            val = pc->val;
        }
        pc = t.tree_successor(pc);
    }
    if (count == 1) dist++;
    return dist;
}

#endif //ASD_ESERCIZI_H
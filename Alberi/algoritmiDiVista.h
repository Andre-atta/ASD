//
// Created by Andrea on 20/03/2026.
//

#ifndef ASD_ALGORITMIDIVISTA_H
#define ASD_ALGORITMIDIVISTA_H

#include "alberiBinari.h"
#include "iostream"
#include "queue"
#include "stack"

/** TEOREMA
 * Se r è la radice di un sottoalbero di n nodi, la chiamata di
 * visita DFS(r) richiede il tempo Θ(n).
 *
 * @param r = nodo radice
 * @param S = stack con politica LIFO
 */
inline void visitaDFS(Pnode r) {
    if (!r) return;

    stack<Pnode> S;
    S.push(r); // push aggiunge il parametro passato in cima allo stack


    while (!S.empty()) {
        auto n = S.top(); // estrai il nodo in cima allo stack
        S.pop(); // poi lo rimuovo

        cout << n->val << " ";  // visita il nodo n

        if (n->dx) S.push(n->dx); // se il nodo ha figlio destro lo butto nello stack
        if (n->sx) S.push(n->sx); // viceversa
    }
}

// DFS visita in preordine
inline void visitaDFS_rec(Pnode r) {
    if (r) {
        cout << r->val << " ";
        visitaDFS_rec(r->sx);
        visitaDFS_rec(r->dx);
    }
}



#endif //ASD_ALGORITMIDIVISTA_H
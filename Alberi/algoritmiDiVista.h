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
inline void visitaDFS(Pnode r)
{
    if (!r) return;

    stack<Pnode> S;
    S.push(r); // push aggiunge il parametro passato in cima allo stack

    while (!S.empty())
    {
        auto n = S.top(); // estrai il nodo in cima allo stack
        S.pop(); // poi lo rimuovo

        cout << char(n->val) << " "; // visita il nodo n

        if (n->dx) S.push(n->dx); // se il nodo ha figlio destro lo butto nello stack
        if (n->sx) S.push(n->sx); // viceversa
    }
}

// DFS visita in preordine (LIFO)
inline void visitaDFS_pre(Pnode r)
{
    if (r)
    {
        cout << char(r->val) << " ";
        visitaDFS_pre(r->sx);
        visitaDFS_pre(r->dx);
    }
}

// DFS visita simmetrica
inline void visitaDFS_simm(Pnode r)
{
    if (r)
    {
        visitaDFS_simm(r->sx);
        cout << char(r->val) << " ";
        visitaDFS_simm(r->dx);
    }
}

// DFS visita postordine
inline void visitaDFS_post(Pnode r)
{
    if (r)
    {
        visitaDFS_post(r->sx);
        visitaDFS_post(r->dx);
        cout << char(r->val) << " ";
    }
}

// BFS Visita in ampiezza (FIFO)
/** Complessità
 *
 * O(n)
 */
inline void visitaBFS(Pnode r)
{
    if (!r) return;

    queue<Pnode> C;
    C.push(r);

    while (!C.empty())
    {
        auto u = C.front();
        C.pop();


        cout << char(u->val) << " ";
        if (u->sx) C.push(u->sx);
        if (u->dx) C.push(u->dx);
    }
}


#endif //ASD_ALGORITMIDIVISTA_H

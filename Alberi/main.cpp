#include "iostream"
#include "Esercizi.h"
#include "alberiBinari.h"
#include "algoritmiDiVista.h"
#include "alberiBinariDiRicerca.h"


int nodo_centrale(Pnode r)
{
    int leaf{0};
    return nodo_centrale_aux(r, 0, leaf);
}

bool tre_bilanciato(Pnode r)
{
    if (!r) return true;
    int min, max{0};
    return tre_bilanciato_aux(r, min, max) <=3;
}

int main()
{
    // alberoBinario albero ('A');
    // Pnode rootA = albero.getRoot();
    // Pnode nL = albero.insert(rootA, 'L', true);
    // Pnode nB = albero.insert(rootA, 'B', false);
    // albero.insert(nL, 'E', true);
    // albero.insert(nL, 'R', false);
    // albero.insert(nB, 'O', true);

    alberoBinario albero (1);
    Pnode rootA = albero.getRoot();
    Pnode nL = albero.insert(rootA, 2, true);
    Pnode nB = albero.insert(rootA, 3, false);
    albero.insert(nL, 4, true);
    albero.insert(nL, 5, false);
    albero.insert(nB, 6, true);



    // Richiamo i tre algoritmi di visita
    std::cout << "\n=== ALGORITMI DI VISITA ===\n\n";

    std::cout << "1. Visita DFS (9.5.2): ";
    visitaDFS(albero.getRoot());
    std::cout << "\n";
    std::cout << "  1.1 Visita DFS_rec (9.5.2): ";
    visitaDFS_pre(albero.getRoot());
    std::cout << "\n";
    std::cout << "  1.2 Visita DFS_simm (9.5.2): ";
    visitaDFS_simm(albero.getRoot());
    std::cout << "\n";
    std::cout << "  1.3 Visita DFS_post (9.5.2): ";
    visitaDFS_post(albero.getRoot());
    std::cout << "\n";
    // std::cout << "2. Visita BFS (9.5.2): ";
    // visitaBFS(albero.getRoot());
    // std::cout << "\n";
    //
    // alberoBinario casoBaso(1);
    //
    // alberoBinario alberoCentrale(0);
    // Pnode rootC = alberoCentrale.getRoot();
    // Pnode c1 = alberoCentrale.insert(rootC, 2, true);
    // alberoCentrale.insert(rootC, 3, false);
    // alberoCentrale.insert(c1, 1, true);
    // alberoCentrale.insert(c1, -1, false);
    //
    // std::cout << "\n=== NUMERO NODI CENTRALI ===\n\n";
    // cout << "numero nodi centrali: " << nodo_centrale(alberoCentrale.getRoot()) << endl;
    // cout << "numero nodi centrali: " << nodo_centrale(casoBaso.getRoot()) << endl;
    //
    //
    // // COSTRUZIONE MANUALE DELL'ALBERO 3-BILANCIATO DELLA FIGURA
    // alberoBinario treBilanciato(0); // Radice a livello 0
    // Pnode root = treBilanciato.getRoot();
    //
    // // Livello 1 (figli della radice)
    // root->sx = new Node(1); root->sx->p = root;
    // root->dx = new Node(2); root->dx->p = root;
    //
    // // Livello 2
    // root->sx->sx = new Node(3); root->sx->sx->p = root->sx; // "Nodo nero a sx"
    // root->sx->dx = new Node(4); root->sx->dx->p = root->sx;
    // root->dx->sx = new Node(5); root->dx->sx->p = root->dx; // "Terzo nodo da sx vuoto"
    // root->dx->dx = new Node(6); root->dx->dx->p = root->dx; // "Nodo nero a dx"
    //
    // // Livello 3
    // root->sx->sx->sx = new Node(7); root->sx->sx->sx->p = root->sx->sx;
    // // root->sx->sx->dx MANCANTE -> Qui il cammino termina a lunghezza 2 (nodo nero sx)
    //
    // root->sx->dx->sx = new Node(8); root->sx->dx->sx->p = root->sx->dx;
    // root->sx->dx->dx = new Node(9); root->sx->dx->dx->p = root->sx->dx;
    //
    // // root->dx->sx NON ha figli -> Qui il cammino termina a lunghezza 2 (terzo nodo)
    //
    // root->dx->dx->sx = new Node(10); root->dx->dx->sx->p = root->dx->dx;
    // // root->dx->dx->dx MANCANTE -> Qui il cammino termina a lunghezza 2 (nodo nero dx)
    //
    // // Livello 4 (Ramo più profondo a sinistra)
    // root->sx->sx->sx->sx = new Node(11); root->sx->sx->sx->sx->p = root->sx->sx->sx;
    // // Foglia finale -> Il cammino più lungo termina qui a lunghezza 4
    //
    // std::cout << "\n=== ALBERO 3 BILANCIATO ===\n\n";
    // std::cout << "È tre bilanciato?: ";
    //
    // // N.B. Ho corretto il passaggio del parametro da casoBaso.getRoot() a treBilanciato.getRoot()
    // if (tre_bilanciato(treBilanciato.getRoot()))
    //     std::cout << "si" << std::endl;
    // else
    //     std::cout << "no" << std::endl;

    return 0;
}

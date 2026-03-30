#include "alberiBinari.h"
#include "algoritmiDiVista.h"
#include "iostream"

int main()
{
    alberoBinario albero (1);
    albero.insert(2);
    albero.insert(3);
    albero.insert(4);
    albero.insert(5);


    // Richiamo i tre algoritmi di visita
    std::cout << "\n=== ALGORITMI DI VISITA ===\n\n";

    std::cout << "1. Visita DFS (9.5.2): ";
    visitaDFS(albero.getRoot());
    std::cout << "\n";
    std::cout << "1.1 Visita DFS_rec (9.5.2): ";
    visitaDFS_rec(albero.getRoot());
    std::cout << "\n";

    return 0;
}
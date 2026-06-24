#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; // Rappresenta +infinito

// Struttura per un arco pesato
struct Edge {
    int to;
    int weight;
};

// 1. BREADTH-FIRST SEARCH (BFS)
// Funziona su grafi non pesati (qui ignoriamo il peso)
void BFS(int start, const vector<vector<Edge>>& adj) {
    cout << "\n=== ESECUZIONE BFS (Partenza da " << start << ") ===\n";
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;

    // Passo 1: Metto la radice in coda
    visited[start] = true;
    q.push(start);
    cout << "[BFS] Inserisco in coda la radice: " << start << "\n";

    while (!q.empty()) {
        // Passo 2: Estraggo il nodo in testa
        int u = q.front();
        q.pop();
        cout << "[BFS] Estraggo dalla coda: " << u << "\n";

        // Passo 3: Esploro i vicini non visitati
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                cout << "      -> Trovo vicino non visitato: " << v << ". Lo marco e lo accodo.\n";
            }
        }
    }
}

// 2. DIJKSTRA
// Funziona con pesi >= 0. Usa una Coda di Priorità (Min-Heap)
void Dijkstra(int start, const vector<vector<Edge>>& adj) {
    cout << "\n=== ESECUZIONE DIJKSTRA (Partenza da " << start << ") ===\n";
    int n = adj.size();

    // Vettori d[] (stime) e pi[] (predecessori)
    vector<int> d(n, INF);
    vector<int> pi(n, -1);

    // Min-Heap: memorizza coppie {distanza, nodo}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Inizializzazione (Init-Single-Source)
    d[start] = 0;
    pq.push({0, start});
    cout << "[DIJKSTRA] Init: d[" << start << "] = 0, tutti gli altri a +INF.\n";

    while (!pq.empty()) {
        // Passo 3: Estraggo il nodo u con stima minima
        int d_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Se trovo una stima vecchia in coda, la ignoro
        if (d_u > d[u]) continue;

        cout << "\n[DIJKSTRA] Estratto u=" << u << " con stima ottima d[" << u << "] = " << d[u] << "\n";

        // Passo 4: Relax degli archi adiacenti
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            cout << "      -> Tento Relax arco (" << u << "->" << v << "), peso " << w << ": ";

            // LA MAGICA DISUGUAGLIANZA TRIANGOLARE
            if (d[u] + w < d[v]) {
                cout << "SUCCESSO! " << d[u] + w << " < " << (d[v] == INF ? "+INF" : to_string(d[v])) << ". Aggiorno d[" << v << "] e pi[" << v << "]=" << u << "\n";
                d[v] = d[u] + w;
                pi[v] = u;
                pq.push({d[v], v}); // Inserisco la nuova stima migliorata
            } else {
                cout << "FALLITA. Nessun miglioramento.\n";
            }
        }
    }

    cout << "\n ALGORITMO TERMINATO, PERCORSO OTTIMALE INDIVIDUATO [";
    for (auto e : d) {cout << e<< ", ";}
    cout << "]"<<endl;

    cout << "\n ALLISTA PREDECESSORI [";
    for (auto e : pi) {cout << e<< ", ";}
    cout << "]";
}

int main() {
    int V = 5; // Nodi da 0 a 4
    vector<vector<Edge>> adj(V);

    // Costruiamo un piccolo grafo di test
    // 0 -> 1 (peso 10)
    // 0 -> 3 (peso 5)
    // 1 -> 2 (peso 1)
    // 3 -> 1 (peso 3)
    // 3 -> 4 (peso 2)
    // 4 -> 2 (peso 9)
    // 4 -> 0 (peso 7) - Ritorno

    adj[0].push_back({1, 10});
    adj[0].push_back({3, 5});
    adj[1].push_back({2, 1});
    adj[3].push_back({1, 3});
    adj[3].push_back({4, 2});
    adj[4].push_back({2, 9});


    adj[0].push_back({1, 3});
    adj[0].push_back({2, 5});
    adj[1].push_back({3, 2});
    adj[2].push_back({3, 1});
    adj[3].push_back({4, 4});
    adj[3].push_back({5, 8});
    adj[4].push_back({5, 3});

    BFS(0, adj);
    Dijkstra(0, adj);

    return 0;
}
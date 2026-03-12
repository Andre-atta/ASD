#include <vector>
#include "iostream"

using namespace std;

/** ! Classe 1: Chaining
 *
 * HASH FUNCTIONS:
 * - Metodo della divisione (primario): h(k) = k % m
 *   * Semplice e veloce
 *   * VINCOLO: m deve essere PRIMO (cruciale per evitare clustering) ed evitare 2 o 10 e i loro multipli
 *   * Dato n elementi, m = findNextPrime(n)
 *
 * - Metodo della moltiplicazione (complementare): h(k) = ⌊m·(k·A mod 1)⌋, con 0 < A < 1
 *   * Implementato per completezza teorica
 *   * A = 0.610033 (inverso sezione aurea, consiglio di Knuth)
 *   * m non deve necessariamente essere primo (più flessibile)
 *
 * FATTORE DI CARICO:
 * - Per Chaining: α = n/m può essere > 1 (le liste si allungano ma funzionano)
 * - Ricerca media: O(1 + α)
 *
 * REHASHING:
 * - Attualmente n è FISSO per semplicità
 * - Se n fosse dinamico, al raggiungimento di una soglia (es. α > 1.5 per Chaining)
 *   bisognerebbe eseguire rehashing:
 *   1. Calcolare m_new = findNextPrime(n / α_target)
 *   2. Creare nuovo array di dimensione m_new
 *   3. Per ogni elemento nel vecchio array: ricalcolare h_new(chiave) = chiave % m_new
 *   4. Reinsiere nella nuova posizione
 *   5. Eliminare vecchio array
 * - Costo operazione: O(n), ma ammortizzato su più inserimenti → O(1) ammortizzato
 *
 */
class myMapChaining
{
    struct Node
    {
        int key;
        int val;
        Node* next;
    };

    typedef Node* PNode;

    vector<PNode> map; // sfrutto la key e la hash function per capire in che indice posizionare i nodi
    int m; // numero chiavi
    int n; // num elementi totali

    int hashFun(int key)
    {
        return key % m;
    } // sfrutta metodo divisione
    int hashFunMultiply(int key)
    {
        return (int)(m * (key * 0.610033 - (int)(key * 0.610033)));
    } // sfrutta li metodo della moltiplicazione
    static void destroy_table(PNode head)
    {
        if (!head) return;
        while (head)
        {
            auto tmp{head};
            head = head->next;
            delete tmp;
        }
    };

public:
    myMapChaining(int m)
    {
        this->m = m;
        this->n = 0;
        map.resize(m, nullptr);
    }

    ~myMapChaining()
    {
        for (auto e : map)
            destroy_table(e);
    }

    /*
     * tempo costante O(1) perchè metto sempre in testa, alla lista
     */
    void insert(int key, int val)
    {
        int index = hashFun(key);

        // Controlla se chiave esiste già -> aggiorno il valore e esco
        PNode current = map.at(index);
        while (current)
        {
            if (current->key == key)
            {
                current->val = val;
                return;
            }
            current = current->next;
        }

        // key nuova, quindi inserisco nuovo nodo (sfrutto key per capire dove posizionarlo)
        auto newNode = new Node{key, val, map.at(index)};
        map.at(index) = newNode;
        n++;
    }

    /* Complessità variabile:
    *  Formula generale: O(1 + α) dove α = n/m è il fattore di carico
    *
    *  Caso medio (ipotesi hashing uniforme):
    *    - Se n = O(m): allora α = O(1) → ricerca O(1)
    *    - Ricerca costante se il numero di elementi cresce proporzionalmente alle celle
    *
    *  Caso pessimo:
    *    - O(n) se tutte le n chiavi collidono nella stessa cella
    *    - Accade raramente con buone funzioni hash
    */
    PNode search(int key)
    {
        int index = hashFun(key);
        auto pc = map.at(index);
        while (pc && pc->key != key)
            pc = pc->next;
        return pc ? pc : nullptr;
    }

    /* Complessità variabile:
    *  Formula generale: O(1 + α) dove α = n/m è il fattore di carico
    *
    *  Caso medio (ipotesi hashing uniforme):
    *    - Se n = O(m): allora α = O(1) → ricerca O(1)
    *    - Ricerca costante se il numero di elementi cresce proporzionalmente alle celle
    *
    *  Caso pessimo:
    *    - O(n) se tutte le n chiavi collidono nella stessa cella
    *    - Accade raramente con buone funzioni hash
    *
    */
    void remove(int key)
    {
        int index = hashFun(key);
        auto pc = map.at(index);

        // Caso 1: Il primo nodo è quello da rimuovere
        if (pc && pc->key == key)
        {
            map.at(index) = pc->next;
            delete pc;
            n--;
            return;
        }

        // Caso 2: Scorrere la lista per trovare il precedente
        while (pc && pc->next)
        {
            if (pc->next->key == key)
            {
                auto temp = pc->next;
                pc->next = pc->next->next;
                delete temp;
                n--;
                return;
            }
            pc = pc->next;
        }
    }

    void printMap()
    {
        cout << "\n+=======================================================+\n";
        cout << "|          CONTENUTO DELLA HASH TABLE (Chaining)      |\n";
        cout << "+-------+------+--------------------------------------+\n";
        cout << "| Index | Nodi | Contenuto                            |\n";
        cout << "+-------+------+--------------------------------------+\n";

        for (int i = 0; i < m; i++)
        {
            int nodeCount = 0;
            PNode temp = map[i];
            while (temp)
            {
                nodeCount++;
                temp = temp->next;
            }

            // Formattazione indice
            cout << "|   " << (i < 10 ? " " : "") << i << "   |  "
                << nodeCount << "   | ";

            // Stampa i nodi nella lista
            if (map[i] == nullptr)
            {
                cout << "[VUOTO]";
            }
            else
            {
                PNode current = map[i];
                bool first = true;
                while (current)
                {
                    if (!first) cout << " -> ";
                    cout << "[" << current->key << ":" << current->val << "]";
                    current = current->next;
                    first = false;
                }
            }
            cout << " |\n";
        }

        cout << "+-------+------+--------------------------------------+\n";
        cout << "| Stats | n=" << n << " m=" << m
            << " alpha=" << (double)n / m << "                    |\n";
        cout << "+=======================================================+\n\n";
    }

    void printSearchResult(int key)
    {
        PNode result = search(key);
        if (result)
        {
            cout << "[FOUND] Chiave " << key << " trovata -> Valore: " << result->val << "\n";
        }
        else
        {
            cout << "[NOT FOUND] Chiave " << key << " NON trovata\n";
        }
    }

    [[nodiscard]] int getM() const { return m; }
    [[nodiscard]] int getN() const { return n; }
};

void myMapChainingTest()
{
    cout << "\n=====================================================================\n";
    cout << "              TEST HASH TABLE - CHAINING METHOD                 \n";
    cout << "=====================================================================\n\n";

    // Crea una hash table con m=13 (numero primo)
    myMapChaining hashTable(13);

    cout << "=> TEST 1: Inserimento di elementi casuali\n";
    cout << "-------------------------------------------\n";
    hashTable.insert(15, 100);
    cout << "  [OK] Inserito: key=15, val=100\n";
    hashTable.insert(25, 200);
    cout << "  [OK] Inserito: key=25, val=200\n";
    hashTable.insert(38, 300);
    cout << "  [OK] Inserito: key=38, val=300\n";
    hashTable.insert(41, 400);
    cout << "  [OK] Inserito: key=41, val=400\n";
    hashTable.insert(52, 500);
    cout << "  [OK] Inserito: key=52, val=500\n";
    hashTable.insert(7, 700);
    cout << "  [OK] Inserito: key=7, val=700\n";

    hashTable.printMap();

    cout << "=> TEST 2: Ricerca di elementi esistenti\n";
    cout << "----------------------------------------\n";
    hashTable.printSearchResult(15);
    hashTable.printSearchResult(25);
    hashTable.printSearchResult(52);
    cout << "\n";

    cout << "=> TEST 3: Ricerca di elementi NON esistenti\n";
    cout << "-------------------------------------------\n";
    hashTable.printSearchResult(99);
    hashTable.printSearchResult(13);
    hashTable.printSearchResult(1000);
    cout << "\n";

    cout << "=> TEST 4: Inserimento con chiave DUPLICATA (aggiornamento valore)\n";
    cout << "-------------------------------------------------------------------\n";
    cout << "  Prima dell'aggiornamento:\n";
    hashTable.printSearchResult(25);
    cout << "  ^ Aggiornamento: insert(key=25, val=999)\n";
    hashTable.insert(25, 999);
    cout << "  Dopo l'aggiornamento:\n";
    hashTable.printSearchResult(25);
    hashTable.printMap();

    cout << "=> TEST 5: Creazione di collisioni deliberate\n";
    cout << "--------------------------------------------\n";
    cout << "  Chiavi che generano lo stesso hash (h(k) = k % 13):\n";
    cout << "  h(3) = 3, h(16) = 3, h(29) = 3 (tutte hashano a indice 3)\n";
    hashTable.insert(3, 111);
    cout << "  [OK] Inserito: key=3, val=111\n";
    hashTable.insert(16, 222);
    cout << "  [OK] Inserito: key=16, val=222\n";
    hashTable.insert(29, 333);
    cout << "  [OK] Inserito: key=29, val=333\n";
    hashTable.printMap();

    cout << "=> TEST 6: Ricerca tra elementi con collisioni\n";
    cout << "---------------------------------------------\n";
    hashTable.printSearchResult(3);
    hashTable.printSearchResult(16);
    hashTable.printSearchResult(29);
    cout << "\n";

    cout << "=> TEST 7: Cancellazione di elementi\n";
    cout << "------------------------------------\n";
    cout << "  Cancellazione: remove(key=15)\n";
    hashTable.remove(15);
    cout << "  [OK] Elemento rimosso\n\n";
    cout << "  Cancellazione: remove(key=25)\n";
    hashTable.remove(25);
    cout << "  [OK] Elemento rimosso\n\n";
    cout << "  Cancellazione: remove(key=16) [collisione, secondo in lista]\n";
    hashTable.remove(16);
    cout << "  [OK] Elemento rimosso\n";
    hashTable.printMap();

    cout << "=> TEST 8: Verifica dopo cancellazioni\n";
    cout << "-------------------------------------\n";
    hashTable.printSearchResult(15);
    hashTable.printSearchResult(25);
    hashTable.printSearchResult(16);
    hashTable.printSearchResult(3);
    cout << "\n";

    cout << "=> TEST 9: Cancellazione del PRIMO elemento in una lista (collisione)\n";
    cout << "----------------------------------------------------------------------\n";
    cout << "  Prima: ";
    hashTable.printSearchResult(29);
    cout << "  Cancellazione: remove(key=29) [primo in lista all'indice 3]\n";
    hashTable.remove(29);
    cout << "  Dopo cancellazione:\n";
    hashTable.printSearchResult(29);
    hashTable.printSearchResult(3);
    hashTable.printMap();

    cout << "=> TEST 10: Inserimento di ulteriori elementi\n";
    cout << "-------------------------------------------\n";
    hashTable.insert(50, 5000);
    cout << "  [OK] Inserito: key=50, val=5000\n";
    hashTable.insert(63, 6300);
    cout << "  [OK] Inserito: key=63, val=6300\n";
    hashTable.insert(77, 7700);
    cout << "  [OK] Inserito: key=77, val=7700\n";
    hashTable.printMap();

    cout << "=> TEST 11: Statistiche finali\n";
    cout << "----------------------------\n";
    cout << "  Numero elementi inseriti (n): " << hashTable.getN() << "\n";
    cout << "  Dimensione tabella (m): " << hashTable.getM() << "\n";
    cout << "  Fattore di carico (alpha = n/m): " << (double)hashTable.getN() / hashTable.getM() << "\n";
    cout << "  Complessita media ricerca: O(1 + alpha) = O("
        << (1.0 + (double)hashTable.getN() / hashTable.getM()) << ")\n\n";

    cout << "=====================================================================\n";
    cout << "                        TEST COMPLETATO                         \n";
    cout << "=====================================================================\n\n";
}

/** ! Classe 2: Open Addressing con ispezione lineare
 *
 * ricordiamo α = n/m (fattore di carico, con n elementi inseriti e m celle)
 *
 * HASH FUNCTIONS:
 * - h(k, i) = (h'(k) + i) % m   con h'(k) = k % m
 * - se la cella è occupata, si incrementa i e si ricalcola la posizione
 *
 * FATTORE DI CARICO:
 * - Ricerca media: O(1/(1-α))
 * - α deve rimanere < 1 (idealmente < 0.7)
 *
 * ISPEZIONE LINEARE (gestione collisioni):
 * - se la cella è occupata, ispeziono linearmente la prossima -> i+1
 * - soffre di addensamento primario: lunghe sequenze di celle adiacenti
 *
 * CANCELLAZIONE:
 * - NON si svuota la cella, si marca con deleted = true
 * - altrimenti si interromperebbe la catena di ispezione per le ricerche future
 */
class myMapOpenLinear
{
    struct Entry
    {
        int key;
        int val;
        bool occupied;
        bool deleted;
    };

    vector<Entry> map;
    int m;
    int n;

    // consideriamo il numero di miss fatti
    int hashFun(int key, int i)
    {
        return (hashFunPrimary(key) + i) % m;
    }
    int hashFunPrimary(int key) const
    {
        return key % m; // funzione hash primaria h'(k)
    }

public:
    myMapOpenLinear(int m)
    {
        this->m = m;
        this->n = 0;
        map.resize(m);
    }
    ~myMapOpenLinear() = default;


    // TODO comlessità
    void insert(int key, int val)
    {
        int i{0}, miss{0};
        bool find{false};

        do
        {
            int index{hashFun(key, i)};
            if (!map.at(index).occupied || map.at(index).deleted) {
                map.at(index) = {key, val, true, false};
                n++;
                cout << "  [INSERTED] key=" << key << " at index " << index
                     << " (collisioni: " << miss << ")\n";
                find = true;
            } else if (map[index].key == key && !map[index].deleted) {
                map[index].val = val;
                cout << "  [UPDATED] key=" << key << " (già esistente)\n";
                find = true;
            } else {
                miss++;
                i++;
            }
        }
        while (!find && i < m);

        if (!find) cout << "  [ERROR] Tabella piena! Impossibile inserire key=" << key << "\n";
    }

    Entry search(int key)
    {
        int i{0}, miss{0};

        do {
            int index{hashFun(key, i)};

            if (!map[index].occupied) {
                cout << "  [NOT FOUND] Chiave " << key << " non trovata\n";
                return Entry{-1, -1, false, false};
            }

            if (map[index].key == key && !map[index].deleted) {
                cout << "  [FOUND] Chiave " << key << " trovata (miss: " << miss << ")\n";
                return map[index];
            }

            miss++;
            i++;

        } while (i < m);

        cout << "  [NOT FOUND] Chiave " << key << " non trovata (tabella esplorata)\n";
        return Entry{-1, -1, false, false};
    }

    void remove(int key)
    {
        int i{0}, miss{0};
        bool removed{false};
        do
        {
            int index {hashFun(key, i)};
            if (map[index].key == key && !map[index].deleted) {
                cout << "  [FOUND] Chiave " << key << " trovata (miss: " << miss << ")\n";
                map.at(index).deleted = true;
                n--;
                removed = true;
            }

            miss++;
            i++;

        } while (i < m && !removed);

        cout << "  [NOT FOUND] Chiave " << key << " non trovata (tabella esplorata)\n";
    }
};


int main()
{
    myMapChainingTest();
    return 0;
}

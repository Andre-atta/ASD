# Alberi - Modulo 1

## Descrizione
Questa sezione copre la teoria riguardante gli **alberi** (capitoli 8-13).

## Struttura della Cartella

```
Alberi/
├── main.cpp              # File principale con test generici
├── alberiBinari.h        # Header con implementazione Alberi Binari
└── README.md             # Questo file
```

## Architettura

### File Header (`.h`)
Ogni tipologia di albero è **completamente implementata in un file header dedicato**:
- Dichiarazioni delle classi
- Implementazioni dei metodi (inline)
- Strutture dati interne

### main.cpp
Contiene:
- Include di tutti gli header degli alberi
- Funzioni di test generiche
- Esecuzione dei test per ogni tipo di albero

## Compilazione
La compilazione è gestita da **CMakeLists.txt**:
Il compilatore include automaticamente tutti gli header utilizzati nel `main.cpp`.

---------------------

# TEORIA DEGLI ALBERI

Un albero radicato è una coppia T = (N, A) dove:
- N èun insieme finito di nodi fra cui si distingue un nodo r detto radice
- A ⊆ N×N è un insieme di coppie di nodi, detti archi

In un albero, ogni nodo v (eccetto la radice) ha esattamente un genitore (o padre) u tale che esiste un arco (u, v) ∈ A.

## DEFINIZIONI
- un nodo può avere 0 o più figli
- il numero di figli di un nodo è detto grado
- un nodo senza figli è detto **foglia**
- un nodo *NON FOGLIA* è detto **nodo interno**
- due nodi con lo stesso PADRE sono detti fratelli

#### LUNGHEZZA == numero archi del cammino oppure numero di nodi che formano il cammino -1
`NB: Esiste sempre un cammino di lunghezza 0 (u => u)`

**DISCENDENTE**
- dato un albero radicato T e presi due nodi appartenenti a questo, x e y, diremo che `x è discendente di y` sse x è figlio diretto o non di y.
- possiamo anche dire che: andando a tracciare il cammino da y ad una foglia dell'albero, deve essere presente x
- NB. ogni nodo è discendente di sé stesso

**ANTENATO**
- dato un albero radicato T e presi due nodi appartenenti a questo, x e y, diremo che `y è antenato di x` sse x è discendente di y.
- possiamo anche dire che: esiste un cammino (che scende verso il basso) che parte da y e arriva a x
- NB. ogni nodo è antenato di sé stesso

`Se y è un antenato di x e x è diverso da y, allora y è un antenato proprio di x, e x è un discendente proprio di y.`

- Il **sottoalbero** con radice in x è l’albero indotto dai discendenti di x.
- La **profondità** di un nodo x è la lunghezza del cammino dalla radice a x.
- Un **livello** di un albero è costituito da tutti i nodi che stanno alla stessa profondità.
- L’**altezza** di un nodo è la lunghezza del più lungo cammino che scende dal nodo x a una foglia.
  - L'altezza di un albero è l'altezza della sua radice, ed è anche uguale alla profondità massima di un qualsiasi nodo dell'albero
---

## Paragrafi 9.3 / 9.4

sostanzialmente trattano i metodi principali per rappresentare la struttura dati "Albero" nella memoria del computer:
- tramite **Array**
- tramite **Puntatori**

e mostra matematicamente il costo di operazioni comuni come 
- `padre(Tree P, Node v) → Node U {NIL}`
- `figli(Tree P, Node v) → List of Node`

In sintesi: Se hai un albero con un numero di figli fisso (come un albero binario) si usano i normali puntatori ai figli. Se hai un albero con un numero di figli variabile e imprevedibile, la rappresentazione "Figlio sinistro - Fratello destro" è in assoluto l'approccio migliore e più elegante. Gli array, invece, si usano quasi esclusivamente per strutture molto specifiche come gli Heap.

---
## Alberi binari ([alberiBinari.h](alberiBinari.h))

sono un caso speciale degli alberi k-ari dove k = 2 <br>
`!! un albero vuoto è un albero binario -> spesso è il nostro caso base`

#### NB:
- definiamo albero completo un albero k-ario dove vale che
  - tutte le foglie hanno la stessa profondità
  - tutti i nodi interni hanno grado k (esattamente k figli)

---
# Algoritmi di visita
Gli algoritmi di visita permettono di esplorare l'albero.
Il tempo di esecuzione per la visita dell'intero albero è O(n) poiché ogni nodo viene visitato una sola volta

Tra gli algoritmi di visita ne evidenziamo due tipologie
### [DFS](algoritmiDiVista.h) (Depth-First Search - Visita in profondità): 
- Esplora i rami il più in profondità possibile prima di tornare indietro. Può essere implementata con una struttura dati Stack (politica LIFO) o tramite ricorsione
![](images/vistaDFS.png)

Per questa tipologia di vista abbiamo tre tipo di visite ricorsive:
1. Pre-ordine (anticipata): Visita Radice → Figlio Sinistro → Figlio Destro.
2. Simmetrica (In-order): Visita Figlio Sinistro → Radice → Figlio Destro. (Cruciale per i BST).
3. Post-ordine (posticipata): Visita Figlio Sinistro → Figlio Destro → Radice.

-> tutte le casistiche sono riportare a codice e analizzate opportunamente

### [BFS](algoritmiDiVista.h) (Breadth-First Search - Visita in ampiezza): 
- Visita tutti i nodi di una determinata profondità prima di scendere al livello successivo. Utilizza una struttura dati Queue (politica FIFO)




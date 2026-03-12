# Tabelle Hash - Capitolo 18

## 18.2 Introduzione alle Tabelle Hash

Le **tabelle hash** offrono un'importante alternativa alle tabelle ad indirizzamento diretto, senza ereditarne l'elevata complessità spaziale.

### Principio fondamentale

Invece di memorizzare la chiave `k` nella posizione `k`, applichiamo una funzione hash `h` che ritorna un indice:
- Funzione hash: `h : U → {0, 1, ..., m-1}`
- **U**: universo di tutte le possibili chiavi (|U| = w)
- **m**: dimensione della tabella (m << w)
- **α = n/m**: fattore di carico (rapporto tra elementi inseriti e celle)

### Vantaggi

- **Spazio**: Riducibile a **Θ(|K|)** invece di Θ(w), dove |K| è il numero di chiavi effettivamente memorizzate
- **Tempo di ricerca**: Costante nel caso medio, dipende dal metodo di gestione delle collisioni

### Notazione

- **w = |U|**: cardinalità dell'universo
- **n = |K|**: numero di elementi inseriti
- **m**: dimensione della tabella hash

---

## 18.3 Gestione delle Collisioni

Una **collisione** si verifica quando la funzione hash mappa due chiavi distinte nella stessa cella:
- h(k₁) = h(k₂) con k₁ ≠ k₂

Esistono due metodi principali per risolverle.

---

## 18.3.1 Concatenamento (Chaining)

Ogni cella della tabella contiene un **puntatore a una lista concatenata** di tutti gli elementi mappati in quella posizione.

### Operazioni

- **Inserimento**: O(1) - l'elemento viene inserito in testa alla lista
- **Cancellazione**: O(1) con liste doppiamente concatenate (fornendo il puntatore all'elemento)
- **Ricerca**: Θ(1+α) nel caso medio (ipotesi di hashing uniforme semplice)
  - Ogni chiave ha la stessa probabilità di finire in qualsiasi cella
  - Se n = O(m), allora α = O(1) → ricerca O(1)
  - Caso pessimo: O(n) se tutte le chiavi collidono

### Vantaggi e svantaggi

✅ Semplice da implementare  
✅ Buono per cancellazioni frequenti  
✅ Prestazioni degradabili in modo prevedibile  
❌ Memoria aggiuntiva per i puntatori delle liste

---

## 18.3.3 Funzioni Hash

L'obiettivo di una buona funzione hash è **distribuire le chiavi uniformemente e casualmente** all'interno della tabella.

### Metodo della Divisione

`h(k) = k mod m`

**Proprietà:**
- Semplice da implementare
- **⚠️ Importante**: m non deve essere una potenza di 2 o 10
- **Ideale**: m deve essere un numero primo lontano dalle potenze di 2

### Metodo della Moltiplicazione

`h(k) = ⌊m · (k·A mod 1)⌋`, dove 0 < A < 1

**Proprietà:**
- La scelta di m è meno critica
- **Consiglio di Knuth**: usare A = φ⁻¹ ≈ 0.610033 (inverso della sezione aurea)
- Complessità maggiore ma migliore distribuzione

### Hashing Universale

- Scelta **casuale di una funzione hash** all'inizio dell'esecuzione da un insieme prestabilito
- Previene casi patologici dove specifici input causano sempre collisioni massime
- Garantisce buone prestazioni in media indipendentemente dai dati di input

---

## 18.3.4 Indirizzamento Aperto (Open Addressing)

Tutti gli elementi sono memorizzati **direttamente nella tabella**, senza liste esterne.

### Principio

Se la cella calcolata è occupata, si calcola una **nuova posizione** secondo una sequenza di ispezioni finché non si trova una cella vuota.

### Funzione hash generalizzata

`h(k, i)` - riceve chiave e numero di ispezioni fallite

- `i = 0, 1, 2, ..., m-1` fino a trovare una cella vuota
- Sequenza di ispezioni dipende dal metodo scelto

### Cancellazione (Importante!)

Più complessa rispetto al chaining:
- **Non si può** svuotare direttamente una cella cancellata (interromperebbe le catene di ricerca)
- Si usa un **marcatore speciale DELETED** al posto di NIL
- **⚠️ Problema**: Le prestazioni degradano nel tempo con cancellazioni frequenti
- Open Addressing è quindi **meno adatto** per tabelle con molte cancellazioni

---

## 18.3.5 Metodi di Scansione nell'Indirizzamento Aperto

### Ispezione Lineare

`h(k, i) = (h'(k) + i) mod m`

**Caratteristiche:**
- Facile da implementare
- ❌ **Soffre di addensamenti primari**: lunghe sequenze di celle adiacenti occupate rallentano la ricerca
- Cattive prestazioni con alto fattore di carico

### Ispezione Quadratica

`h(k, i) = (h'(k) + c₁·i + c₂·i²) mod m`

**Caratteristiche:**
- Risolve l'addensamento primario
- ❌ **Soffre di addensamento secondario**: chiavi con lo stesso hash iniziale seguono la stessa sequenza di ispezioni
- Migliore di lineare ma ancora non ottima

### Doppio Hashing

`h(k, i) = (h₁(k) + i·h₂(k)) mod m`

**Caratteristiche:**
- ✅ **Metodo migliore** tra i tre
- Utilizza **due funzioni hash indipendenti**:
  - h₁(k) determina la posizione iniziale
  - h₂(k) determina il "passo" (distanza tra ispezioni)
- **Requisito**: h₂(k) e m devono essere **coprimi** per esplorare tutta la tabella
  - Conseguenza: non garantisce di trovare uno slot se la tabella è completamente piena
- Evita sia l'addensamento primario che secondario

---

## Struttura delle Implementazioni

### myMap (Chaining) - IMPLEMENTATO
```
myMap → Concatenamento con liste concatenate
├── insert()      O(1)
├── search()      O(1+α) medio
└── remove()      O(1+α)

Struttura interna:
  - Nodo privato con: chiave, valore, puntatore al prossimo
  - Array di puntatori a liste concatenate
  - Ogni cella punta alla testa di una lista
```

### myMapOpenLinear - DA IMPLEMENTARE
```
myMapOpenLinear → Open Addressing con ispezione lineare
├── insert()      O(1/(1-α))
├── search()      O(1/(1-α))
└── remove()      O(1/(1-α)) complessa con DELETED marker

Struttura interna:
  - Entry privato con: chiave, valore, flag occupied, flag deleted
  - Array di Entry (NON puntatori, elementi diretti)
  - Sequenza di ispezione: (h'(k) + i) mod m
  - Problema: addensamenti primari
```

### myMapOpenQuadratic - DA IMPLEMENTARE
```
myMapOpenQuadratic → Open Addressing con ispezione quadratica
├── insert()      O(1/(1-α))
├── search()      O(1/(1-α)) migliore di lineare
└── remove()      O(1/(1-α)) con DELETED marker

Struttura interna:
  - Entry privato con: chiave, valore, flag occupied, flag deleted
  - Array di Entry (NON puntatori, elementi diretti)
  - Sequenza di ispezione: (h'(k) + c₁·i + c₂·i²) mod m
  - Migliore di lineare (elimina addensamenti primari)
  - Problema: addensamenti secondari
```

### myMapDoubleHash - DA IMPLEMENTARE
```
myMapDoubleHash → Open Addressing con doppio hashing
├── insert()      O(1/(1-α)) migliore tra i tre
├── search()      O(1/(1-α))
└── remove()      O(1/(1-α)) con DELETED marker

Struttura interna:
  - Entry privato con: chiave, valore, flag occupied, flag deleted
  - Array di Entry (NON puntatori, elementi diretti)
  - Due funzioni hash indipendenti: h₁(k) e h₂(k)
  - Sequenza di ispezione: (h₁(k) + i·h₂(k)) mod m
  - Requisito: h₂(k) e m devono essere coprimi
  - Elimina sia addensamenti primari che secondari
```

---

## Tabella Comparativa

| Aspetto | Chaining | Lineare | Quadratica | Doppio Hash |
|---------|----------|---------|-----------|-----------|
| **Insert** | O(1) | O(1/(1-α)) | O(1/(1-α)) | O(1/(1-α)) |
| **Search (successo)** | O(1+α) | O(1/(1-α)) | O(1/(1-α)) | O(1/(1-α)) |
| **Search (insuccesso)** | O(1+α) | O(1/(1-α)) | O(1/(1-α)) | O(1/(1-α)) |
| **Remove** | O(1+α)* | Complessa | Complessa | Complessa |
| **Cancellazioni frequenti** | ✅ Ottimo | ⚠️ Degrada | ⚠️ Degrada | ⚠️ Degrada |
| **Memoria aggiuntiva** | Sì (liste) | No | No | No |
| **α massimo consigliato** | > 1 | < 0.7 | < 0.7 | < 0.7 |
| **Addensamento primario** | N/A | ❌ Sì | ✅ No | ✅ No |
| **Addensamento secondario** | N/A | N/A | ❌ Sì | ✅ No |

*Con liste doppiamente concatenate diventa O(1)

---

## Differenze Critiche nel Design

### Chaining (Implementazione attuale ✅)

**Struttura dei nodi:**
- Nodo privato con: chiave, valore, puntatore al prossimo

**Struttura dell'array:**
- Vettore di puntatori a liste concatenate
- Ogni cella contiene l'indirizzo del primo nodo della lista
- Le celle vuote puntano a nullptr

**Vantaggi:**
- Semplice da implementare
- Buono per cancellazioni frequenti
- α può crescere oltre 1

### Open Addressing (Tutte e tre le varianti)

**Struttura delle entry:**
- Entry privato con: chiave, valore, flag occupied (booleano), flag deleted (booleano)

**Struttura dell'array:**
- Vettore di Entry (NON puntatori!)
- Gli elementi sono memorizzati direttamente nella tabella
- Le celle utilizza i flag per tracciare lo stato

**Perché i flag `deleted`?**
- Non puoi semplicemente svuotare una cella quando cancelli
- Interromperebbe la sequenza di ispezione durante le ricerche future
- Il marcatore DELETED comunica "questo slot era occupato, continua a cercare"

**Vincolo cruciale:**
- α deve rimanere < 1 (idealmente < 0.7)
- Quando α supera la soglia, è necessario ridimensionare la tabella

---

## Schema di Test Suggerito

**Obiettivo:** Confrontare i tempi di esecuzione delle quattro implementazioni

**Parametri di test:**
- Dimensione della tabella: m (numero primo)
- Numero di elementi inseriti: n
- Fattore di carico: α = n/m
- Tipo di chiavi: casuali / sequenziali / con collisioni deliberate

**Procedure da misurare:**
- Tempo di inserimento di n elementi
- Tempo di ricerca (successo e insuccesso)
- Tempo di cancellazione (se implementata)
- Numero totale di ispezioni (per Open Addressing)
- Numero di collisioni

**Risultati attesi:**

- Durante i test, mantenere α costante per confronti equi
- Suggerimento: testare con α = 0.5, 0.75, 0.9
- Quando α raggiunge una soglia (es. 0.75), ridimensionare la tabella
- Chaining: Costante O(1) indipendentemente da α
- Lineare: Migliore di Chaining con basso α, peggiore con alto α
- Quadratica: Migliore di Lineare, peggiore di Doppio Hashing
- Doppio Hashing: Migliore tra i tre metodi di Open Addressing

---

## Note di Implementazione Generali

### Fattore di Carico α = n/m

- **Chaining**: Funziona bene anche con α > 1, ma le liste si allungano
- **Open Addressing**: Deve rimanere α < 1, idealmente α < 0.7
- Quando α supera la soglia: ridimensionare la tabella e rihashare tutti gli elementi

### Quando usare quale metodo

1. **Se cancellazioni frequenti**: Preferire **Chaining**
2. **Se memoria limitata e poche cancellazioni**: **Open Addressing** (qualsiasi variante)
3. **Se velocità critica**: **Doppio Hashing**
4. **Se prototipo veloce**: **Chaining**
5. **Se dati casuali ben distribuiti**: Anche **Ispezione Lineare** potrebbe essere sufficiente


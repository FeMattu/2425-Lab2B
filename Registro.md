##  Introduzione ad array, puntatori e file (introC)


**Lezione 1** (17/9/24)

* Introduzione al linguaggio C. Esempio di lettura e scrittura di interi dal terminale. Compilazione: errori e warning. Permessi di lettura scrittura esecuzione `rwx`. Esecuzione di programmi. Array "statici" (tipo `int a[n]` in `somma.c`) vs array "dinamici" gestiti con `malloc/free` utilizzati in `sommad.c`

-----------------------

**Lezione 2** (20/9/24)

* Allocazione dinamica di array in C. Funzioni: malloc/free/realloc. Programma `primi.c`.
* Utilizzo di *valgrind* per verificare il corretto utilizzo e deallocazione degli array

-------

**Lezione 3** (24/9/24)

* Introduzione ai puntatori; uso di puntatori negli array.
* Significato e uso di `*` e `&`
* Esempio passaggio parametri per riferimento attraverso un puntatore: `parametri.c` e `sommadprod.c`


-------

**Lezione 4** (27/9/24)

* Rappresentazione di stringhe in C
* Uso dei parametri argc/argv di main()
* introduzione al *makefile*; compilazione con il comando *make*

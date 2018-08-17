/*

grafo.c

dipendenze: grafo.hpp, grafofn.c

Sorgente realizzato da
Vincenzo Consiglio (07-11-1980) consiglio.vincenzo@email.it
Studente universitario presso la
Università di Messina
Facoltà di Scienze MM. FF. NN.
Laurea in Informatica
Curriculum: Progettazione e gestione di sistemi informatici

Realizzato in data 21 Febbraio 2005

*/
#include <stdio.h>
#include <stdlib.h>

float target[25]; // matrici max 1x25,, 5x5 
int righe,colonne;

typedef struct collegamento{
  int v1,v2,w;
  struct collegamento *next;
}link;

int menu(); // menu principale
void letturaMatriceIncidenza(); // lettura matrice di incidenza da file
void stampaMatriceIncidenza(); // stampa matrice di incidenza precedentemente caricata in memoria
int algoritmi(); // menu per la scelta degli algoritmi
int algFourQueens(long *row, int n); //algoritmo delle quattro regine
void stampaMatrice (long *row, int n); //funzione che stampa lo stato corrente dell'algoritmod elle 4 regine
int conflicts(long *row, int k); // funzione che controlla eventuali conflitti nel posizionamento di una regina
void prim(); // algoritmo per la ricerca dell'MST col metodo di Prim
int creazioneGrafo(link *inizioLista); // funzione per la creazione di una struttura per il contenimento dei dati di un grafo
int autoCreaGrafo(link *inizioLista); // funzione che carica in memoria il grafo dell'esempio di pag 343 figura 7.4.1
int cercaArco(link *inizioLista, int j, int k); // funzione per la ricerca di un particolare peso di un arco richiesto

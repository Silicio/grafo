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
#include "grafofn.c"

int main(){
  int n;
  while(1){
    switch(menu()){
      case 1:{
        letturaMatriceIncidenza();
        break;
      }
      case 2:{
        stampaMatriceIncidenza();
        break;
      }      
      case 3:{
        switch(algoritmi()){
          case 1:{
            system("CLS");
            printf("\nInserire il numero di righe o colonne della matrice nxn: ");
	        scanf("%d",&n);
	        long row[n];
            if(!algFourQueens(row,n)) printf("\n\nL'algoritmo non ha trovato nessuna soluzione\n");
	        else printf("\n\nL'algoritmo ha trovato almeno una soluzione\n");
            system("PAUSE");
            break;	      
          }
          case 2:{
            prim();
            system("Pause");
            break;	      
          }
        }
        break;
      }
      case 0:{
        free (target);
        exit(0);
        break;
      }
    }
  }
  return (0);
}
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
#define MAXSIZE 100
#include "grafo.hpp"
#define MAX 50

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
int menu(){
  int scelta=-1;
  system("cls");
  while ((scelta<0)||(scelta>5)){
    printf("\t\t\tRICERCA OPERATIVA v0.3.2\n\n\n");
    printf("\t\t\t\tMain Menu\n\n");
    printf("\t1) Leggi Matrice di Incidenza da un file\n");
    printf("\t2) Stampa Matrice di Incidenza\n");
    printf("\t3) Algoritmi\n");
    printf("\n\t0) Esci\n");
    scanf("%d",&scelta);
  }
  return scelta;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
void stampaMatriceIncidenza(){
  int i=0,j,p=colonne;
  printf("\n");
  for (j=0;j<righe;j++){ // ciclo per stampare iteramente le righe
    printf("|");
    for (i;i<p;i++) printf("%5.1f ",target[i]); // Ciclo che stampa una riga alla volta
    printf("|\n");
    p+=colonne;
  }
  printf("\n");
  system("PAUSE");	
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void letturaMatriceIncidenza(){
  int i=0,p,n,j;
  char path[20];
  FILE *fp=NULL;
  printf("\nLettura della matrice\n");
  while (!fp){
      printf("Inserire il nome del file comprensivo di estensione, eventualmente inserendo tutto il path:\n");
      scanf("%s",path);
      if(!(fp=fopen(path,"r"))) fprintf(stderr,"Errore nell'apertura del file \"%s\" o file non trovato.\n\n",path);
  }
  printf("Inserisci il numero delle m colonne: ");
  scanf("%d",&colonne);
  printf("Inserisci il numero delle n righe: ");
  scanf("%d",&righe);
  puts("\nLettura da file...");
  n=(righe)*(colonne);
  for (i=0;i<n;i++) fscanf(fp,"%f",&target[i]);
  puts("\nLettura completata con successo.");
  stampaMatriceIncidenza();
  fclose(fp);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
int algoritmi(){
  int scelta=-1;
  system("cls");
  while ((scelta<0)||(scelta>2)){
    printf("\t\t\t\tALGORITMI\n\n");
    printf("\t1) Le Quattro Regine\n");
    printf("\t2) Prim\n");
    printf("\n\t0) Esci\n");
    scanf("%d",&scelta);
  }
  return scelta;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Algoritmo che controlla se nella posizione corrente è possibile piazzare una regina o no
// Restituisce 0 se non ci sono conflitti, altrimenti restituisce 1

int conflicts(long *row, int k){
  int iterator;
  if (k>0){
    iterator=k-1;
    while(iterator>=0) {
      if (row[iterator]==row[k]) return 1; // controllo se la regina è nella stessa riga o colonna con un altra
      if ((row[iterator]-iterator)==(row[k]-k)) return 1; // controllo sulla diagonale obliqua verso il basso
      if ((row[iterator]+iterator)==(row[k]+k)) return 1; // controllo sulla diagonale obliqua verso l'alto
      iterator--;
     }
  }        
  return 0;    
}    

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Algoritmo delle 4 regine.
// L'algoritmo restituisce Vero (1) se esiste la soluzione, ovvero Falso (0) se nn ce n'è
int algFourQueens(long *row, int n){
  int k=0,i=0; 
  for (i;i<n;i++) row[i]=-1; // inizializzo lo stack per i dati
  row[k]=0;
  stampaMatrice(row,n);
  k++;
  while (k>=0) {
      row[k]=row[k]+1;
      while ((row[k]<n)&&(conflicts(row,k))) {
          stampaMatrice(row,n);
          row[k]=row[k]+1;
      }    
      if (row[k]<n) {
          if (k==(n-1)) {
            stampaMatrice(row,n);
            return(1);
          }
          else {
              stampaMatrice(row,n);
              k++;
          }
      }
      else { //backtrack        
        row[k]=-1;
         k--;
        stampaMatrice(row,n);
      }    
  }
  return (0);
}        

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Funzione che stampa la matrice con le regine eventualmente posizionate, alla fine mette il processo in pausa per 0,1 secondi
void stampaMatrice(long row[], int n){
  int j=0,i;
  system("CLS");
  printf("\n-");
  for (i=0;i<n;i++) printf("--");
  printf("\n");
  for (j;j<n;j++){
    printf("|");
    for (i=0;i<n;i++){
      if (row[i]==j) printf("X|");
      else printf(" |");
    }
    printf("\n-");
    for (i=0;i<n;i++) printf("--");
    printf("\n");
  }
  for (i=0;i<n;i++){
      if (row[i]==-1) printf("| ");
      else printf("|%d",row[i]);
  }
  printf("|\n");
  sleep(100);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// Questa Funzione crea un struttura lista, in cui vengono memorizzati i dati del grafo da costruire
// La funzione restituisce il numero di vertice del grafo

int creazioneGrafo(link *inizioLista){
  int m,n,i,k;
  link *temp,*ultimoLista; //temp è il puntatore temporaneo all'area di memoria della struttura che si si sta modificando
  ultimoLista=inizioLista; //ultimoLista mi server per collegare l'ultimo elemento a quello nuovo
  system("CLS");
  printf("Inserire il numero di vertici del grafo: ");
  scanf("%d",&m);
  printf("Inserire il numero di archi del grafo: ");
  scanf("%d",&n);
  for (i=0;i<m;i++){ // ciclo per inserire i link degli intorni di ogni nodo
    printf("Inserire il grado di intorno del vertice %d: ",i);
    scanf("%d",&k);
    for (k;k>0;k--){ //ciclo per inserire tutti i link di ogni nodo 
      temp=(link *)malloc(sizeof(link));
      printf("Inserisci la coppia i j di vertici ed il relativo peso w (es: 1 2 7): ");    
      scanf("%d %d %d",&temp->v1,&temp->v2,&temp->w);
      ultimoLista->next=temp;
      temp->next=NULL;
      ultimoLista=temp;
    }     
  }
  return m; // ritorna il numero di vertici
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Questa funzione auto crea un grafo prestabilito
int autoCreaGrafo(link *inizioLista){
    link *temp,*ultimoLista;
    ultimoLista=inizioLista;
//  creazione arco w(0,2)=2
    temp=(link *)malloc(sizeof(link));
    temp->v1=0;
    temp->v2=2;
    temp->w=2;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(0,1)=4
    temp=(link *)malloc(sizeof(link));
    temp->v1=0;
    temp->v2=1;
    temp->w=4;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(0,4)=3
    temp=(link *)malloc(sizeof(link));
    temp->v1=0;
    temp->v2=4;
    temp->w=3;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(2,0)=2
    temp=(link *)malloc(sizeof(link));
    temp->v1=2;
    temp->v2=0;
    temp->w=2;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(1,0)=2
    temp=(link *)malloc(sizeof(link));
    temp->v1=1;
    temp->v2=0;
    temp->w=4;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(4,0)=3
    temp=(link *)malloc(sizeof(link));
    temp->v1=4;
    temp->v2=0;
    temp->w=3;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(1,3)=5
    temp=(link *)malloc(sizeof(link));
    temp->v1=1;
    temp->v2=3;
    temp->w=5;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(3,1)=5
    temp=(link *)malloc(sizeof(link));
    temp->v1=3;
    temp->v2=1;
    temp->w=5;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(2,3)=1
    temp=(link *)malloc(sizeof(link));
    temp->v1=2;
    temp->v2=3;
    temp->w=1;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(3,2)=1
    temp=(link *)malloc(sizeof(link));
    temp->v1=3;
    temp->v2=2;
    temp->w=1;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(3,5)=6
    temp=(link *)malloc(sizeof(link));
    temp->v1=3;
    temp->v2=5;
    temp->w=6;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(5,3)=6
    temp=(link *)malloc(sizeof(link));
    temp->v1=5;
    temp->v2=3;
    temp->w=6;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(5,2)=3
    temp=(link *)malloc(sizeof(link));
    temp->v1=5;
    temp->v2=2;
    temp->w=3;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(2,5)=3
    temp=(link *)malloc(sizeof(link));
    temp->v1=2;
    temp->v2=5;
    temp->w=3;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(5,4)=2
    temp=(link *)malloc(sizeof(link));
    temp->v1=5;
    temp->v2=3;
    temp->w=2;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(4,5)=2
    temp=(link *)malloc(sizeof(link));
    temp->v1=4;
    temp->v2=5;
    temp->w=2;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(2,4)=6
    temp=(link *)malloc(sizeof(link));
    temp->v1=2;
    temp->v2=4;
    temp->w=6;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
//  creazione arco w(4,2)=6
    temp=(link *)malloc(sizeof(link));
    temp->v1=4;
    temp->v2=2;
    temp->w=6;
    ultimoLista->next=temp;
    temp->next=NULL;
    ultimoLista=temp;
    return 6;
}


// +++++++++++++++++++++++++++++++++++++++++++++++
// la funzione riceve il puntatore all'inizio della lista, e l'arco composto dai due vertici da ricercare
// la funzione se trova l'arco richiesto, ne restituisce il peso
// altrimenti restituisce il valore massimo per un intero
int cercaArco(link *inizioLista, int j, int k){
  link *temp;
  temp=(inizioLista->next);
  do{
    if(((temp->v1)==j)&&((temp->v2)==k)) return (temp->w);
    temp=(temp->next);
  }while(temp);
  return (32767);
} 

/* ++++++++++++++++++++++++++++++++++++++++++++++++
   Questa è l'implementazione dell'algoritmo di Prim per la ricerca Del Minimum Spanning Tree
   prende in considerazione grafi con al più 25 vertici.
   v(i)=1 se il vertice è stato aggiunto nel MST
   v(i)=0 se il vertice non fa parte del MST
*/
void prim(){
  int scelta=0,i,ciclo,s,m,k,nArchi,count=0,j,add_vertex,min,pesoCorrente,pesoFinale=0,e[2],v[25],E[98]; //E[] array del MST, v[] array dei vertici, s è il vertice di partenza...
  link *temp,*inizioLista;
  inizioLista=(link *)malloc(sizeof(link));
  while((scelta<1)||(scelta>2)){
    system("CLS");
    printf("1) Inserisci manualmente un nuovo grafo\n");
    printf("2) Carica in memoria un grafo preconfigurato (pag.343 figura 7.4.1)\n");
    scanf("%d",&scelta);
    if (scelta==1) m=creazioneGrafo(inizioLista);
    if (scelta==2) m=autoCreaGrafo(inizioLista);
  }
  nArchi=2*(m-1);
  printf("Seleziona il vertice di partenza: ");
  scanf("%d",&s);
  for(i=0 ; i<m ; i++) v[i]=0;
  for (i=0 ; i<nArchi ; i++) E[i]=-1; //inizializzazione con un insieme vuoto di archi
  count=0;
  v[s]=1; //Vertice di partenza
  for (i=0 ; i<m-1 ; i++) { // ciclo per inserire gli m-1 archi nel minimum spanning tree
    min=32767;
    for(j=0 ; j<m ; j++){ // ciclo per selezionare iteramente il primo nodo
      if (v[j]==1){  // il nodo da considerare deve appartenere già all'mst
        for(k=0 ; k<m ; k++){ // ciclo per verificare tutti i possibili archi non appartententi all'MST
          pesoCorrente=cercaArco(inizioLista,j,k);
          if((v[k]==0)&&(pesoCorrente < min)){ //se il vertice k non fa parte dell'mst ed il peso corrente è minore di min...
            add_vertex=k; // memorizziamo il vertice k
            e[0]=j;  // memorizziamo in un array temporaneo l'arco 
            e[1]=k;  // (j,k)
            min=pesoCorrente; // salvo il peso minimo corrente nella variabile min per successivi confronti
          }
        }
      }
    }
    pesoFinale+=min;
    v[add_vertex]=1; // Il vertice in add_vertex trovato viene inserito nell'MST
    E[count]=e[0]; // mi salvo l'arco appena trovato
    count++;
    E[count]=e[1]; // in un array che contiene tutti gli archi dell'MST
    count++;
  }
  system("CLS");
  printf("Il Minimum Spanning Tree e':\n");
  for(ciclo=0 ; ciclo < nArchi ; ){ // ciclo per stampare l'MST
    printf("(%d,",E[ciclo]);
    ciclo++;
    printf("%d)-->",E[ciclo]);
    ciclo++;
  }
  printf("NULL\n\nIl peso del Minimum Spanning Tree e' %d\n\n",pesoFinale);
//  Istruzioni per pulire la memoria
  temp=inizioLista;
  while(temp){
    temp=temp->next;
    free(temp);
  }
  free(inizioLista);
}
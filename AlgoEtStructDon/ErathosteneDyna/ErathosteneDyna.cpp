//---------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include "cmath"
#include "cstdio"
#include "../InOut/src/inout.h"

using namespace std; 

//---------------------------------------------------------------------------
// const int MAX = 1000000;
const int MAX = 2147483647;
struct TListePrem{
  int  nbrMax;
  int* pPrem;
  int  nbrPrem;
};
//---------------------------------------------------------------------------
void InitialiserTListePrem(TListePrem& listePrem);
void Erathostene(TListePrem& l);
void AfficherPremiers(TListePrem l);
void DetruireTListePrem(TListePrem& listePrem);
//  ...
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  TListePrem listePrem;
  do {
    InitialiserTListePrem(listePrem);
    cout << endl << "Votre naturel maximum ? ";
    listePrem.nbrMax = ReadInt("",0,MAX);
    Erathostene(listePrem);
    AfficherPremiers(listePrem);
    DetruireTListePrem(listePrem);
  } while (!Stop());
  return 0;
}
//---------------------------------------------------------------------------

void InitialiserTListePrem(TListePrem& listePrem){
  listePrem.nbrMax = 0;
  listePrem.pPrem = NULL;
  listePrem.nbrPrem = 0;
}

void Erathostene(TListePrem& l){
  bool* bools = NULL;
  int i, nb, k, bools_size;
  double racine;
  clock_t t = clock();

  /*lancer l'algo seulement si il existe au moins 1 prem*/
  if(l.nbrMax >= 2){

    /* init du nbre max de prems == au nbre d'impairs*/
    bools_size = (l.nbrMax/2)+(l.nbrMax%2);

    // bools = calloc(bools_size, sizeof(bool));
    bools = new bool[bools_size];
    l.nbrPrem = bools_size;
  
    /*tableau de bool deja initialisé a true partout si true == 0 !*/
    for (i = 1; i <= l.nbrMax/2; ++i)
        bools[i] = true;
    bools[0] = false;

    /*Erato defini le nombre max d'iteration 
    comme la racine du nombre maximum*/
    racine = sqrt(l.nbrMax);

    /*itérer pour tous les impairs jusqu'à la racine*/
    for (nb = 3; nb <= racine; nb+=2)
      if(bools[nb/2] == true){  /* l'impair considéré est il un premier? */
        k = l.nbrMax / nb; /* si oui, combien a-t-il de multiple jusqu'au max? */
        /* Effacer tout les multiples */
        for (i = nb; i <= k; i+=2)
          if(bools[(i * nb)/2] == true){
            bools[(i * nb)/2] = false;
            /* for each bool toggle from true to false */
            /* decrement the total number of prems */
            l.nbrPrem--; 
          }
      } 

    // l.pPrem = calloc(l.nbrPrem + 1, sizeof(int));
    l.pPrem = new int[l.nbrPrem + 1];
    nb = 0;
    l.pPrem[nb++] = 2; /* si il existe au moins un prem, il == 2 */
    //  remplir le tableau de prems en fct des indices de bools à true
    for (i = 1; i <= bools_size; ++i)
      if (bools[i] == true)
        l.pPrem[nb++] = (i*2)+1;

    delete [] bools;
  }

  t = clock() - t;
  // printf("Duree calculs : %.2f\n", (float)t / 1000000);
  cout << "Duree calculs : " << (float)t / 1000000 << endl;
}

void AfficherPremiers(TListePrem l){
  int i;
  cout << "Il y a " << l.nbrPrem << " nombre premiers inferieurs a " << l.nbrMax << "." << endl;

  if (l.nbrPrem > 20)
  {
    for (i = 0; i < 10; ++i)
      cout << "Nombre premier n " << i + 1 << " : " << l.pPrem[i] << endl;
    printf("\n...\n\n");
    for (i = l.nbrPrem-10; i < l.nbrPrem; ++i)
      cout << "Nombre premier n " << i + 1 << " : " << l.pPrem[i]  << endl;
  }
  else{
    for (i = 0; i < l.nbrPrem; ++i)
      cout << "Nombre premier n " << i + 1 << " : " << l.pPrem[i]  << endl;
  }
}

void DetruireTListePrem(TListePrem& l){
  l.nbrPrem=0;
  l.nbrMax=0;
  delete [] l.pPrem; 
}
//---------------------------------------------------------------------------


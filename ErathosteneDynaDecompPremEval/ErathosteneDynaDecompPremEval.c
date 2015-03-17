/*
 ============================================================================
 Name        : ErathosteneDynaDecomEval.c
 Author      : JM Mattens
 Version     :
 Copyright   :
 Description :
 Comment     : use C99
               C Compiler Options: -pedantic;-Wall;-std=c99
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <stdint.h>   // C99 -> uint8_t, int8_t, int32_t, int64_t, ...
#include <inttypes.h> // C99 -> printf("%" PRId32 ", %" PRIu8 "\n",myint32,myunit8), ...
#include <stdbool.h>  // C99 -> bool, true, false

#define MAX_FACT 15

struct TPrimesList { // old name : TListePrem
    int32_t nbrMax;
    int32_t* pPrimes; // old name : pPrimes
    int cPrimes;      // old name : nbrPrem
};

struct TPrimesFact {
    int64_t number;
    int sign;
    int cFact;
    int64_t* pFact;
    int8_t* pPow;
};

void InitializeTPrimesFact(struct TPrimesFact* ppf);
void DestroyTPrimesFact(struct TPrimesFact* ppf);
void ShowPrimesFactorization(struct TPrimesFact* ppf);

void InitializeTPrimesList(struct TPrimesList* ppl);
void Erathostene(struct TPrimesList* ppl);
void DestroyTPrimesList(struct TPrimesList* ppl);
void ShowPrimesList(struct TPrimesList* ppl);
void MyTests(struct TPrimesFact* ppf, struct TPrimesList* ppl);

void PrimesFactorization(struct TPrimesFact* ppf, struct TPrimesList* ppl);
bool VerifyPrimesFactorization(struct TPrimesFact* ppf);

int main(int argc, char* argv[])
{
    clock_t ct1, ct2;
    struct TPrimesFact primesFact;
    InitializeTPrimesFact(&primesFact);

    MyTests(&primesFact, NULL);

    struct TPrimesList listPrimes; // C99 -> can declare variable here

    // InitializeTPrimesList(&listPrimes); // old name :InitialiserTListePrem
    // listPrimes.nbrMax = 0;
    // Erathostene(&listPrimes);
    // MyTests(&primesFact, &listPrimes);
    // DestroyTPrimesList(&listPrimes); // old name : DetruireTListePrem

    // InitializeTPrimesList(&listPrimes);
    // listPrimes.nbrMax = INT16_MAX; // C99 -> 2^16-1 = 32767
    // printf("\nCalculing array of primes (max=%" PRId32 ")\n",
    //        listPrimes.nbrMax); // C99 : %PRId32, %PRIu32, %PRId8, %PRIu8, ...
    // ct1 = clock();
    // Erathostene(&listPrimes);
    // ct2 = clock();
    // printf("Duree calculs : %.2f\n\n", (double)(ct2 - ct1) / CLOCKS_PER_SEC);
    // MyTests(&primesFact, &listPrimes);
    // DestroyTPrimesList(&listPrimes);

    InitializeTPrimesList(&listPrimes);
    listPrimes.nbrMax = INT32_MAX; // C99 -> 2^31-1 = 2147483647
    printf("\nCalculing array of primes (max=%" PRId32 ")\n",
           listPrimes.nbrMax); // C99 : %PRId32, %PRIu32, %PRId8, %PRIu8, ...
    ct1 = clock();
    Erathostene(&listPrimes);
    ct2 = clock();
    printf("Duree calculs : %.2f\n\n", (double)(ct2 - ct1) / CLOCKS_PER_SEC);
    MyTests(&primesFact, &listPrimes);
    DestroyTPrimesList(&listPrimes);

    DestroyTPrimesFact(&primesFact);
    return EXIT_SUCCESS;
}

void MyTests(struct TPrimesFact* ppf, struct TPrimesList* ppl)
{
    clock_t ct1, ct2;
    int64_t aToTest[] = { INT64_MIN,             INT64_MIN + 1LL,       INT64_MIN + 2LL,      INT32_MIN - 1LL,
                          INT32_MIN,             INT32_MIN + 1LL,       -100LL,               -97LL,
                          -25LL,                 -5LL,                  -4LL,                 -3LL,
                          -2LL,                  -1LL,                  0LL,                  1LL,
                          2LL,                   3LL,                   4LL,                  5LL,
                          25LL,                  97LL,                  100LL,                INT32_MAX - 1LL,
                          INT32_MAX,             INT32_MAX + 1LL,       614889782588491410LL, 9223371873002223329LL,
                          9223371994482243049LL, 9223372036854775783LL, INT64_MAX - 2LL,      INT64_MAX - 1LL,
                          INT64_MAX };
    int size_aToTest = 33;
    if(ppl == NULL) {
        printf("\nCalculing decompositions without array of primes \n");
    } else {
        // C99 : %PRId32, %PRIu32, %PRId8, %PRIu8, ...
        printf("\nCalculing decompositions with array of primes (max=%" PRId32 ")\n", ppl->nbrMax);
        ShowPrimesList(ppl); // old name : AfficherPremiers2
    }

    ct1 = clock();

    for(int i = 0; i < size_aToTest; ++i) {
        ppf->number = aToTest[i];
        PrimesFactorization(ppf, ppl);
        ShowPrimesFactorization(ppf);
        if(!VerifyPrimesFactorization(ppf))
            printf("ERROR for %" PRId64 "\n", ppf->number);
    }

    for(long long int ll = (int64_t)INT32_MIN * INT32_MIN - 25LL; ll < (int64_t)INT32_MIN * INT32_MIN + 25LL;
        ++ll) { // C99 : local ll
        ppf->number = ll;
        PrimesFactorization(ppf, ppl);
        if(!VerifyPrimesFactorization(ppf))
            printf("ERROR for %" PRId64 "\n", ppf->number);
    }
    for(long long int ll = (int64_t)INT16_MIN * INT16_MIN - 100LL; ll < (int64_t)INT16_MIN * INT16_MIN + 100LL; ++ll) {
        ppf->number = ll;
        PrimesFactorization(ppf, ppl);
        if(!VerifyPrimesFactorization(ppf))
            printf("ERROR for %" PRId64 "\n", ppf->number);
    }
    for(long long int ll = -1000LL; ll <= 1000LL; ++ll) {
        ppf->number = ll;
        PrimesFactorization(ppf, ppl);
        if(!VerifyPrimesFactorization(ppf))
            printf("ERROR for %" PRId64 "\n", ppf->number);
    }
    for(long long int ll = (int64_t)INT16_MAX * INT16_MAX - 25LL; ll < (int64_t)INT16_MAX * INT16_MAX + 25LL; ++ll) {
        ppf->number = ll;
        PrimesFactorization(ppf, ppl);
        if(!VerifyPrimesFactorization(ppf))
            printf("ERROR for %" PRId64 "\n", ppf->number);
    }
    for(long long int ll = (int64_t)INT32_MAX * INT32_MAX - 100LL; ll < (int64_t)INT32_MAX * INT32_MAX + 100LL; ++ll) {
        ppf->number = ll;
        PrimesFactorization(ppf, ppl);
        if(!VerifyPrimesFactorization(ppf))
            printf("ERROR for %" PRId64 "\n", ppf->number);
    }

    ct2 = clock();
    printf("Duree calculs : %.2f\n\n", (double)(ct2 - ct1) / CLOCKS_PER_SEC);
}


// TODO ...
/*------------------------------------------------------*/
void InitializeTPrimesFact(struct TPrimesFact* ppf){
    ppf->number = 0;
    ppf->sign = 0;
    ppf->cFact = 0;
    ppf->pFact = NULL;
    ppf->pPow = NULL;

    return;
}

/*------------------------------------------------------*/
void DestroyTPrimesFact(struct TPrimesFact* ppf){
    ppf->number = 0;
    ppf->sign = 0;
    ppf->cFact = 0;
    free(ppf->pFact);
    free(ppf->pPow);

    return;
}

/*------------------------------------------------------*/
void InitializeTPrimesList(struct TPrimesList* ppl){
    ppl->nbrMax = 0;
    ppl->pPrimes = NULL;
    ppl->cPrimes = 0;
    
    return;
}

/*------------------------------------------------------*/
void Erathostene(struct TPrimesList* ppl){
    bool* bools = NULL;
    int i, nb, k, bools_size;
    double racine;

    /*lancer l'algo seulement si il existe au moins 1 prem*/
    if(ppl->nbrMax >= 2){

        /* init du nbre max de prems == au nbre d'impairs*/
        bools_size = (ppl->nbrMax/2)+(ppl->nbrMax%2);
        bools = calloc(bools_size, sizeof(bool));
        ppl->cPrimes = bools_size;
    
        /*tableau de bool deja initialisé a true partout si true == 0 !*/
          for (i = 1; i <= ppl->nbrMax/2; ++i)
                bools[i] = true;
        bools[0] = false;

        /*Erato defini le nombre max d'iteration 
        comme la racine du nombre maximum*/
        racine = sqrt(ppl->nbrMax);

        /*itérer pour tous les impairs jusqu'à la racine*/
        for (nb = 3; nb <= racine; nb+=2)
            if(bools[nb/2] == true){    /* l'impair considéré est il un premier? */
                k = ppl->nbrMax / nb; /* si oui, combien a-t-il de multiple jusqu'au max? */
                /* Effacer tout les multiples */
                for (i = nb; i <= k; i+=2)
                    if(bools[(i * nb)/2] == true){
                        bools[(i * nb)/2] = false;
                        /* for each bool toggle from true to false */
                        /* decrement the total number of prems */
                        ppl->cPrimes--; 
                    }
            }   

        ppl->pPrimes = calloc(ppl->cPrimes + 1, sizeof(int));
        nb = 0;
        ppl->pPrimes[nb++] = 2; /* si il existe au moins un prem, il == 2 */
        /* remplir le tableau de prems en fct des indices de bools à true*/
        for (i = 1; i <= bools_size; ++i)
            if (bools[i] == true)
                ppl->pPrimes[nb++] = (i*2)+1;
        free(bools);
    }

    return;
}

/*------------------------------------------------------*/
void DestroyTPrimesList(struct TPrimesList* ppl){
    ppl->cPrimes=0;
    ppl->nbrMax=0;
    free(ppl->pPrimes); /*free() should only be called on memory you allocated (or on NULL).*/

    return;
}

/*------------------------------------------------------*/
void ShowPrimesList(struct TPrimesList* ppl){
    int i;
    printf("Il y a %d nombre premiers inferieurs a %d\n", ppl->cPrimes, ppl->nbrMax);

    if (ppl->cPrimes > 20)
    {
        for (i = 0; i < 10; ++i)
            printf("Nombre premier n %10d : %11d \n", i,ppl->pPrimes[i]);
        printf("\n...\n\n");
        for (i = ppl->cPrimes-10; i < ppl->cPrimes; ++i)
            printf("Nombre premier n %10d : %11d \n", i,ppl->pPrimes[i]);
    }
    else{
        for (i = 0; i < ppl->cPrimes; ++i)
            printf("Nombre premier n %10d : %11d \n", i,ppl->pPrimes[i]);
    }

    return;
}

/*------------------------------------------------------*/
void PrimesFactorization(struct TPrimesFact* ppf, struct TPrimesList* ppl){

    int64_t nb, divider, indice;
    int64_t tPow[MAX_FACT] = {0};
    int64_t tFact[MAX_FACT] = {0};

    if(ppf->number > 0LL){
        ppf->sign = 1;
    }
    else if(ppf->number < 0LL){
        ppf->sign = -1;
    }
    else{
        ppf->sign = 0;
    }

    if(ppf->number == INT64_MIN){
        nb = (ppf->number / 2) * ppf->sign;
        tPow[0]++;
    }
    else{
        nb = ppf->number * ppf->sign;
    }

    int64_t racine = sqrt(nb);
    divider = 2;
    indice = 0;
    ppf->cFact = 0;

    if(ppl == NULL || sizeof(ppl) == 0){
        /* decomposer avec les nombre impairs */
        while(nb > 1){
            
            if (!(nb % divider))
                ppf->cFact++;
            
            while(!(nb % divider) ){
                nb = nb / divider;
                tFact[ppf->cFact-1] = divider;
                tPow[ppf->cFact-1]++;
            }

            if(divider>2)
                divider += 2;
            else
                divider++;
        }
    }

    else{
        divider = ppl->nbrMax;

        if(!(ppl->nbrMax % 2))
            divider++;
        while(nb > 1){
            if(indice < ppl->cPrimes - 1){
                if (!(nb % ppl->pPrimes[indice]))
                    ppf->cFact++;
                
                while(!(nb % ppl->pPrimes[indice])){
                    nb = nb / ppl->pPrimes[indice];
                    tFact[ppf->cFact-1] = ppl->pPrimes[indice];
                    tPow[ppf->cFact-1]++;
                }   
                indice++;
            }else{

                if (!(nb % divider))
                    ppf->cFact++;
                
                while(!(nb % divider)){
                    nb = nb / divider;
                    tFact[ppf->cFact-1] = divider;
                    tPow[ppf->cFact-1]++;
                }

                if(divider>2)
                    divider += 2;
                else
                    divider++;
            }
        }
    }

    ppf->pFact = calloc( ppf->cFact+1, sizeof(int64_t));
    ppf->pPow = calloc( ppf->cFact+1, sizeof(int64_t));

    for (int i = 0; i <= ppf->cFact; ++i){
        ppf->pFact[i] = tFact[i];
        ppf->pPow[i] = tPow[i];
    }

    return;
}

/*------------------------------------------------------*/
bool VerifyPrimesFactorization(struct TPrimesFact* ppf){
    int64_t verify = 1;

    for (int i = ppf->cFact -1 ; i >= 0 ; --i)
        for (int j = 0; j < ppf->pPow[i]; ++j)
            verify *= ppf->pFact[i];

    verify *= ppf->sign;
    
    return (verify == ppf->number);
}

/*------------------------------------------------------*/
void ShowPrimesFactorization(struct TPrimesFact* ppf){

    printf("%"PRId64" = %d",ppf->number, ppf->sign );

    for (int i = 0; i < ppf->cFact; ++i)
        printf(" %"PRId64"^%d",ppf->pFact[i], ppf->pPow[i]);

    printf("\n");

    return;
}





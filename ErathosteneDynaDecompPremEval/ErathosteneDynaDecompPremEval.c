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

struct TPrimesList { // old name : TListePrem
    int32_t nbrMax;
    int32_t* pPrimes; // old name : pPrem
    int cPrimes;      // old name : nbrPrem
};

struct TPrimesFact {
    int64_t number;
    int sign;
    int cFact;
    int64_t* pFact;
    int8_t* pPow;
};

// TODO ...

void MyTests(struct TPrimesFact* ppf, struct TPrimesList* ppl);

int main(int argc, char* argv[])
{
    clock_t ct1, ct2;
    struct TPrimesFact primesFact;
    InitializeTPrimesFact(&primesFact);

    MyTests(&primesFact, NULL);

    struct TPrimesList listPrimes; // C99 -> can declare variable here

    InitializeTPrimesList(&listPrimes); // old name :InitialiserTListePrem
    listPrimes.nbrMax = 0;
    Erathostene(&listPrimes);
    MyTests(&primesFact, &listPrimes);
    DestroyTPrimesList(&listPrimes); // old name : DetruireTListePrem

    InitializeTPrimesList(&listPrimes);
    listPrimes.nbrMax = INT16_MAX; // C99 -> 2^16-1 = 32767
    printf("\nCalculing array of primes (max=%" PRId32 ")\n",
           listPrimes.nbrMax); // C99 : %PRId32, %PRIu32, %PRId8, %PRIu8, ...
    ct1 = clock();
    Erathostene(&listPrimes);
    ct2 = clock();
    printf("Duree calculs : %.2f\n\n", (double)(ct2 - ct1) / CLOCKS_PER_SEC);
    MyTests(&primesFact, &listPrimes);
    DestroyTPrimesList(&listPrimes);

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
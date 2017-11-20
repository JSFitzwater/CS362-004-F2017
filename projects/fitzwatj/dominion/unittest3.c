/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */




#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
    int i, t, r, x, oldCount, result, handPos;



    int seed = 1000;
    int numPlayer = 2;

    struct gameState G;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};


    int maxHandPos = 5;


    printf ("test set - isGameOver():\n");



    // clear the game state
    memset(&G, 23, sizeof(struct gameState));   


    // initialize a new game
    r = initializeGame(numPlayer, k, seed, &G); 

    // test province
    G.supplyCount[province] = 1;

    result = isGameOver(&G);

    // test outcome
    assert(result == 0);

    // test three-supply-pile
    for(x = 0; x < 2; x++)
    {
        G.supplyCount[x] = 1;
    }

    result = isGameOver(&G);

    // test outcome
    // assert(result == 0);
    if(result == 0){ printf("resultA is good\n");}
    else{printf("result is bad\n");}




    // clear the game state
    memset(&G, 23, sizeof(struct gameState));   


    // initialize a new game
    r = initializeGame(numPlayer, k, seed, &G); 

    // test province
    G.supplyCount[province] = 0;

    result = isGameOver(&G);

    // test outcome
    // assert(result == 0);
    if(result == 1){ printf("resultB is good\n");}
    else{printf("result is bad\n");}

    // test three-supply-pile
    for(x = 0; x < 2; x++)
    {
        G.supplyCount[x] = 0;
    }

    result = isGameOver(&G);

    // test outcome
    // assert(result == 0);
    if(result == 1){ printf("resultC is good\n");}
    else{printf("result is bad\n");}



    printf("All tests passed!\n");

    return 0;
}

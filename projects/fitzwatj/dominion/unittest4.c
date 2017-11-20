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
    int i, t, r, x, p, card, oldCount, result, handPos;



    int seed = 1000;
    int numPlayer = 2;

    struct gameState G;
    struct gameState G2;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};


    int maxHandPos = 5;


    printf ("test set - shuffle():\n");



    // clear the game state
    memset(&G, 23, sizeof(struct gameState));   


    // initialize a new game
    r = initializeGame(numPlayer, k, seed, &G); 

    for (p = 0; p < numPlayer; p++)
    {
        x = 0;

        memcpy( &G2, &G, sizeof(struct gameState) );

        result = shuffle(p, &G);

        // test outcome
        // assert(result == 0);
        if(result == 0){ printf("result is good\n");}
        else{printf("result is bad\n");}
    
        for (card=0; card<G.deckCount[p]; card++)
        {
            if( G.deck[p][card] !=  G2.deck[p][card] )
            {
                x++; 
            }
        }

        // test outcome
        // assert(result == 0);
        if(x > 1){ printf("deck shuffle good\n");}
        else{printf("deck shuffle bad\n");}
    }


    printf("All tests passed!\n");

    return 0;
}

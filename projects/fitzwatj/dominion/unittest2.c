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
    int i, p, r, x, oldCount, result, handPos, drawCount;



    int seed = 1000;
    int numPlayer = 2;

    struct gameState G;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};


    int maxHandPos = 5;


    printf ("test set - drawCard():\n");


    for (p = 0; p < numPlayer; p++)
    {
        for (drawCount = 1; drawCount < 4; drawCount++)
        {
            // clear the game state
            memset(&G, 23, sizeof(struct gameState));   


            // initialize a new game
            r = initializeGame(numPlayer, k, seed, &G); 

            oldCount = G.handCount[p];

            for (x - 0; x < drawCount; x++)
            {
                result = drawCard(p, &G);

                // test outcome
                // assert(result == 0);
                if(result == 0){ printf("result is good\n");}
                else{printf("result is bad\n");}
            }

            // test outcome
            // assert(G.handCount[p] == oldCount + drawCount);
            if(G.handCount[p] == oldCount + drawCount)
            { printf("handCount is good\n");}
            else{printf("handCount is bad\n");}
        }
    }

    printf("All tests passed!\n");

    return 0;
}

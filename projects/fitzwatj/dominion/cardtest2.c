
// James Fitzwater
// CS 362.400 - Assignment No. 3




/*
 * Include the following lines in your makefile:
 *
 * cardtest[NUM]: cardtest[NUM].c dominion.o rngs.o
 *      gcc -o cardtest[NUM] -g  cardtest[NUM].c dominion.o rngs.o $(CFLAGS)
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {

    int cardsAdd,
        cardsGone,
        choice1,
        choice2,
        currentPlayer = 0,
        handAmt = 0,
        handPos,
        handMax = 5,
        numPlayers = 2;
        

    int gameSeed = 555;


	int cds[10] = { adventurer, baron, cellar, cutpurse,
                    duchy, laboratory, minion, sea_hag, 
                    smithy, village };

    struct gameState origGame, scratchGame;





//
//  TEST SUMMARY
//
    printf( " - Init test-run, card: smithy - \n\n" );

    /* Init a Working Game */
	initializeGame( numPlayers, cds, gameSeed, &origGame );



//
//  CONDUCT SCENARIO
//
    printf( "Scenario - player draws three cards\n" );

    /* Work with a copy of the init'd game */
    memcpy( &scratchGame, &origGame, sizeof(struct gameState) );


    /* +3 Cards */
    for (i = 0; i <= 3; i++)
    {
        drawCard(currentPlayer, scratchGame);
    }

    discardCard(handPos, currentPlayer, scratchGame, 0);

        /* -- */

    cardsAdd = 3;
    cardsGone = 1;

        /* -- PRINT OUTCOME: CURRENT PLAYER */

    currentPlayer = 0,

    printf( "Current Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayer] + (cardsAdd-cardsGone) );

    printf( "Current Player Deck Status:\n - num cards populating deck: %d \n - num deck cards should be: %d\n\n", scratchGame.deckCount[currentPlayer], origGame.deckCount[currentPlayer] - cardsAdd );

        /* -- PRINT OUTCOME: OPPOSING PLAYER */

    currentPlayer = 1,

    printf( "Opposing Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayerPlayer] + (cardsAdd-cardsGone) );


        /* -- ASSERT: CURRENT PLAYER -- */

    currentPlayer = 0,

    assert( scratchGame.handCount[currentPlayer] == origGame.handCount[currentPlayerPlayer] + (cardsAdd-cardsGone) );

    assert( scratchGame.deckCount[currentPlayer] == origGame.deckCount[currentPlayerPlayer] - cardsAdd );

        /* -- ASSERT: OPPOSING PLAYER -- */

    currentPlayer = 1,

    assert( scratchGame.handCount[currentPlayer] == origGame.handCount[currentPlayerPlayer] + (cardsAdd-cardsGone) );

    assert( scratchGame.deckCount[currentPlayer] == origGame.deckCount[currentPlayerPlayer] - cardsAdd );




    return 0;
}

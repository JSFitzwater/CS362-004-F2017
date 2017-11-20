
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

    int i, j, cardsAdd1,
        cardsAdd2,
        cardsGone1,
        cardsGone2,
        choice1,
        choice2,
        currentPlayer = 0,
        emptyDeckAudit = 0,
        handAmt = 0,
        handPos,
        handMax = 5,
        numPlayers = 2,
        z, cc=0, bb=0, aa=0,
        cardDrawn,
        drawntreasure;

    int *temphand;
    int *thAudit;
    int *dtAudit;
    int *dpAudit;
        

    int gameSeed = 555;


	int cds[10] = { adventurer, baron, village, cutpurse,
                    duchy, village, minion, sea_hag, 
                    smithy, village };

    struct gameState origGame, scratchGame;





//
//  TEST SUMMARY
//
    printf( " - Init test-run, card: adventurer - \n\n" );

    printf( " Adventurer: reveal cards in deck until 2 treasure kinds uncovered (else, stop on full deck seen); then, draw +2 cards and discard those revealed.\n\n" );


    /* Init a Working Game */
	initializeGame( numPlayers, cds, gameSeed, &origGame );




//
//  CONDUCT SCENARIO
//

    /* Work with a copy of the init'd game */
    memcpy( &scratchGame, &origGame, sizeof(struct gameState) );


    while(drawntreasure<2)
    {
        // "if the deck is empty we need to shuffle discard and add to deck"
        if (scratchGame.deckCount[currentPlayer] <1)
        {
            emptyDeckAudit += 1;

            shuffle(currentPlayer, &scratchGame);
        }

        drawCard(currentPlayer, &scratchGame);

        // "top card of hand is most recently drawn card."
        cardDrawn = scratchGame.hand[currentPlayer][scratchGame.handCount[currentPlayer]-1];

        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
        {
            dtAudit += 1;

            drawntreasure++;
        }
        else {
            temphand[z]=cardDrawn;
            
            thAudit[cc++] = temphand[z];
            
            // "this should just remove the top card (the most recently drawn one)."
            scratchGame.handCount[currentPlayer]--; 
            z++;
        }
    }

    while(z-1>=0)
    {
        // "discard all cards in play that have been drawn"
        scratchGame.discard[currentPlayer][scratchGame.discardCount[currentPlayer]++]
			= temphand[z-1]; 

        dpAudit[aa++] = temphand[z-1];

        z=z-1;
    }




//
//  PRINT OUTCOME
//


    printf( "Num treasure cards function indicates seeing: %d \n\n", dtAudit );
    printf( "Num instances deck completely exhausted: %d \n\n", emptyDeckAudit );

    printf( "Player's original hand: " );
    while(origGame.hand[currentPlayer][bb]){
        printf( "%d ", origGame.hand[currentPlayer][bb] );
        bb++;
    }

    printf( "\nAnd, temphand helper saw following cards: ");
    while(thAudit[cc]){
        printf( "%d ", thAudit[cc] );
        cc--;
    }

    printf( "Audit original + TempHand against cards shifted at end into discard.\nCards discarded: " ); 
    while(dpAudit[aa]){
        printf( "%d ", dpAudit[aa] );
        aa--;
    }
    printf("\n\nTest Complete.\n\n");


    return 0;
}

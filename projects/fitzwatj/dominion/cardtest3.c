
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

    int i, j, k, cardsAdd,
        cardsGone,
        choice1,
        choice2,
        outgoingCard,
        cutpurseGold = 2,
        cardsRevealed = 0,
        cpprDiscard = 0,
        currentPlayer = 0,
        handAmt = 0,
        handPos,
        handMax = 5,
        numPlayers = 2;
        

    int gameSeed = 555;


	int cds[10] = { adventurer, baron, village, cutpurse,
                    duchy, village, minion, sea_hag, 
                    smithy, village };

    struct gameState origGame, scratchGame;





//
//  TEST SUMMARY
//
    printf( " - Init test-run, card: cutpurse - \n\n" );


    /* Init a Working Game */
	initializeGame( numPlayers, cds, gameSeed, &origGame );




//
//  CONDUCT SCENARIO
//

    /* Work with a copy of the init'd game */
    memcpy( &scratchGame, &origGame, sizeof(struct gameState) );

    updateCoins(currentPlayer, &scratchGame, cutpurseGold);

    for (i = 0; i < scratchGame.numPlayers; i++)
    {
        if (i != currentPlayer)
        {
            for (j = 0; j < scratchGame.handCount[i]; j++)
            {
                if (scratchGame.hand[i][j] == copper)
                {
                    cpprDiscard += 1;
                    discardCard(j, i, &scratchGame, 0);
                    break;
                }
                if (j == scratchGame.handCount[i])
                {
                    for (k = 0; k < scratchGame.handCount[i]; k++)
                    {
                        if (DEBUG)
                        {
                            cardsRevealed += 1;
                            printf("Player %d reveals card number %d\n", i, scratchGame.hand[i][k]);
                        }
                    }	
                    break;
                }		
            }
            
        }
            
    }				

    j = 0;
    handPos = 0;
    while( j )
    {
        if( scratchGame.hand[currentPlayer][j] == cutpurse )
        {
            handPos = j;
            break;
        }
    }

    //discard played card from hand
    outgoingCard = scratchGame.hand[currentPlayer][handPos];

    discardCard(handPos, currentPlayer, &scratchGame, 0);





        /* -- PRINT OUTCOME: CURRENT PLAYER */

    currentPlayer = 0,

    printf( "Current Player Gold:\n - gold coins now held: %d \n - num gold should be: %d\n\n", scratchGame.coins, origGame.coins + (cutpurseGold) );

    printf( "Current Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayer] -1 );

    printf( "Current Player's Discards:\n - discarded card: %d \n - replaced with: %d \n\n", outgoingCard, scratchGame.hand[currentPlayer][handPos] );


        /* -- PRINT OUTCOME: OPPOSING PLAYER */

    currentPlayer = 1,

    printf( "Opposing Player Gold:\n - gold coins now held: %d \n - num gold should be: %d\n\n", scratchGame.coins, origGame.coins );

    printf( "Opposing Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayer] );

    printf( "Opposing Player Deck Status:\n - num cards populating deck: %d \n - num deck cards should be: %d\n\n", scratchGame.deckCount[currentPlayer], origGame.deckCount[currentPlayer] );

    printf( "Opposing Player's Coppers Result:\n - coppers discarded?" );
    if( cpprDiscard > 0 ){
        printf( " YES  - num discarded: %d\n\n", cpprDiscard );
    } else {
        printf( " NO \n" );
    }

    printf( "\n - held cards revealed?" );
    if( cardsRevealed > 0 ){
        printf( " YES  - num shown: %d\n\n", cardsRevealed );
    } else {
        printf( " NO \n" );
    }

    

        /* -- ASSERT: CURRENT PLAYER -- */

    currentPlayer = 0,

    assert( scratchGame.coins == origGame.coins + (cutpurseGold) );

    assert( scratchGame.handCount[currentPlayer] == origGame.handCount[currentPlayer]- 1 );

    assert( outgoingCard != scratchGame.hand[currentPlayer][handPos] );


        /* -- ASSERT: OPPOSING PLAYER -- */

    currentPlayer = 1,

    assert( scratchGame.coins == origGame.coins - (cpprDiscard) );


    return 0;
}

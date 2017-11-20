
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
    printf( " - Init test-run, card: minion - \n\n" );

    printf( " Minion: player may select one of two options: \n(1) add +2 gold cards, or (2) discard hand and redraw cards \n[then, all other players with 5 cards in-hand redraw 4 cards].\n\n" );


    /* Init a Working Game */
	initializeGame( numPlayers, cds, gameSeed, &origGame );




//
//  CONDUCT SCENARIO ONE
//
    printf( "Scenario 1 - 'int choice1', add 2 gold cards\n" );

    /* Work with a copy of the init'd game */
    memcpy( &scratchGame, &origGame, sizeof(struct gameState) );


    scratchGame.numActions++;

    // discard this card from hand
    discardCard( handPos, currentPlayer, &scratchGame, 0 );

    // +2 coin action to player
    scratchGame.coins = origGame.coins + 2;


        /* -- PRINT OUTCOME: CURRENT PLAYER */

    currentPlayer = 0,

    printf( "Current Player Gold:\n - gold coins now held: %d \n - num gold should be: %d\n\n", scratchGame.coins, origGame.coins + (2) );

    printf( "Current Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayer] );

    printf( "Current Player Deck Status:\n - num cards populating deck: %d \n - num deck cards should be: %d\n\n", scratchGame.deckCount[currentPlayer], origGame.deckCount[currentPlayer] );

        /* -- PRINT OUTCOME: OPPOSING PLAYER */

    currentPlayer = 1,

    printf( "Opposing Player Gold:\n - gold coins now held: %d \n - num gold should be: %d\n\n", scratchGame.coins, origGame.coins );

    printf( "Opposing Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayer] );

    printf( "Opposing Player Deck Status:\n - num cards populating deck: %d \n - num deck cards should be: %d\n\n", scratchGame.deckCount[currentPlayer], origGame.deckCount[currentPlayer] );

        /* -- ASSERT: CURRENT PLAYER -- */

    currentPlayer = 0,

    assert( scratchGame.coins == origGame.coins + (2) );

    assert( scratchGame.handCount[currentPlayer] == origGame.handCount[currentPlayer] + (cardsAdd1-cardsGone1) );

    assert( scratchGame.deckCount[currentPlayer] == origGame.deckCount[currentPlayer] - (cardsAdd1-cardsGone1) );

        /* -- ASSERT: OPPOSING PLAYER -- */

    currentPlayer = 1,

    assert( scratchGame.coins == origGame.coins );

    assert( scratchGame.handCount[currentPlayer] == origGame.handCount[currentPlayer] + (cardsAdd2-cardsGone2) );

    assert( scratchGame.deckCount[currentPlayer] == origGame.deckCount[currentPlayer] - (cardsAdd2-cardsGone2) );




//
//  CONDUCT SCENARIO TWO
//
    printf( "Scenario 2 - 'int choice2', discard & redaraw hand\n" );

    /* Work with a copy of the init'd game */
    memcpy( &scratchGame, &origGame, sizeof(struct gameState) );


	/* 
    ** "discard hand, redraw 4, other players 
    **  with 5+ cards discard hand and draw 4"
    */

    cardsAdd1 = 0;
    cardsAdd2 = 0;
    cardsGone1 = 0;
    cardsGone2 = 0;

    //discard hand
    while(scratchGame.handCount[currentPlayer] > 0)
    {
        cardsGone1 += 1;
        discardCard(handPos, currentPlayer, &scratchGame, 0);
    }

    //draw 4
    for (i = 0; i < 4; i++)
    {
        cardsAdd1 +=1;
        drawCard(currentPlayer, &scratchGame);
    }

    //other players discard hand and redraw if hand size > 4
    for (i = 0; i < scratchGame.numPlayers; i++)
    {
        if (i == currentPlayer)
        {
            if ( scratchGame.handCount[i] > 4 )
            {
                //discard hand
                while( scratchGame.handCount[i] > 0 )
                {
                    cardsGone2 += 1;
                    discardCard(handPos, i, &scratchGame, 0);
                }
                    
                //draw 4
                for (j = 0; j < 4; j++)
                {
                    cardsAdd2 +=1;
                    drawCard(i, &scratchGame);
                }
            }
        }
    }


        /* -- PRINT OUTCOME: CURRENT PLAYER */

    currentPlayer = 0,

    printf( "Current Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayer] + (cardsAdd1-cardsGone1) );

    printf( "Current Player Deck Status:\n - num cards populating deck: %d \n - num deck cards should be: %d\n\n", scratchGame.deckCount[currentPlayer], origGame.deckCount[currentPlayer] - (cardsAdd1-cardsGone1) );

        /* -- PRINT OUTCOME: OPPOSING PLAYER */

    currentPlayer = 1,

    printf( "Opposing Player Hand:\n - num cards now held: %d \n - num held cards should be: %d\n\n", scratchGame.handCount[currentPlayer], origGame.handCount[currentPlayer] + (cardsAdd2-cardsGone2) );

    printf( "Opposing Player Deck Status:\n - num cards populating deck: %d \n - num deck cards should be: %d\n\n", scratchGame.deckCount[currentPlayer], origGame.deckCount[currentPlayer] - (cardsAdd2-cardsGone2) );

        /* -- ASSERT: CURRENT PLAYER -- */

    currentPlayer = 0,

    assert( scratchGame.handCount[currentPlayer] == origGame.handCount[currentPlayer] + (cardsAdd1-cardsGone1) );

    assert( scratchGame.deckCount[currentPlayer] == origGame.deckCount[currentPlayer] - (cardsAdd1-cardsGone1) );

        /* -- ASSERT: OPPOSING PLAYER -- */

    currentPlayer = 1,

    assert( scratchGame.handCount[currentPlayer] == origGame.handCount[currentPlayer] + (cardsAdd2-cardsGone2) );

    assert( scratchGame.deckCount[currentPlayer] == origGame.deckCount[currentPlayer] - (cardsAdd2-cardsGone2) );


    return 0;
}

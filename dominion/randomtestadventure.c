
// James Fitzwater
// CS 362.400 - Assignment No. 3




/*
 * Include the following lines in your makefile:
 *
 * cardtest[NUM]: cardtest[NUM].c dominion.o rngs.o
 *      gcc -o cardtest[NUM] -g  cardtest[NUM].c dominion.o rngs.o $(CFLAGS)
 */



#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define FUZZY_TIMES 10
#define FUZZY_MAX 5

#define MAX_PLYR 2

#define GAME_START_DECK 10
#define NORM_TREASURE 2



int randNum( int iterations )
{
    return( rand() % iterations );
}



/** "Reveal cards from your deck until you reveal 2 Treasure     **
 **  cards. Put those Treasure cards into your hand and discard  **
 **  the other revealed cards."                                  **/

void cardADVENTURER( struct gameState *gState )
{
    int* temphand; 

    int cardDrawn, currPlyr, drawntreasure, 
        randCard, randDiscards, randDiscards2, 
        randDrawCount, randStopDraw, tmp;

    int v=w=x=y=z=0;


    //  ---


    randStopDraw = randNUM( NORM_TREASURE );

    while( drawntreasure <  randStopDraw)
    {
        /* randomize player's recorded deck   *
         * size check up to player's starting *
         * deck size                          */ 

        randShuffleDeck = randNUM( GAME_START_DECK );

        /* empty player deck: shuffle discard for reuse */
 
        if( gState->deckCount[currPlyr] < randShuffleDeck )
        {
            shuffle(currPlyr, gState);
        }


        // ---

        randDrawCount = randNUM( gState->deckCount[currPlyr] );

        /* draw another... now, up to size of deck */

        for( w=0; w<randDrawCount; w++ )
        {
            drawCard(currPlyr, gState);
        }


        // ---

        randCard = randNUM( randDrawCount );
        if( randCard > randDrawCount ){ randCard = randCard - randDrawCount; }

        /* prev: last card rcvd eq "top" card  *
         * now:  last card eq random selection *
         *        from cards player just drew  */

        cardDrawn = gState->hand[currPlyr][gState->handCount[currPlyr] - randCard];


        // ---

        tmp = randNUM() % 2;
        if( tmp!=0 ){ randTreasCount = 2; )else{ randTreasCount = 1; }

        /* if card eq treasure, incr treas tally */

        if( cardDrawn == copper || cardDrawn == silver || cardDrawn == gold )
        {
            drawntreasure = randTreasCount;
        }

        /* else move card to "temphand" for eventual discard */

        else {
            temphand[x] = cardDrawn;
            
            gState->handCount[currPlyr]--; 

            x++;
        }
    }


    // ---

    randDiscards = randNUM( v );
    if( randDiscards > v ){ randDiscards = randDiscards - v; }
    randDiscards2 = randDiscards;

    /* empty (discard) cards shifted to our "temphand" (seen card) */

    while( (randDiscards-1) >= 0)
    {
        gState->discard[currPlyr][gState->discardCount[currPlyr]++] 
         = temphand[randDiscards-1]; 

        randDiscards--;
    }


    // ---

    /* print current game state */

    printf( "outcome: ADVENTURER\n"
            "  treas count to trigger stop - %d\n"
            "  deck min to trigger shuffle  - %d\n"
            "  card count drawn (last gen'd) - %d\n"
            "  hand pos for drawn card - %d\n"
            "  treas count (last gen'd) - %d\n",
            "  discarded from temphand - %d\n",
            randStopDraw,randShuffleDeck,
            randDrawCountrandCard,randTreasCount,
            randDiscards);

    printf("  plyr curr hand: ");
    for( x=0; x<MAX_PLYR; x++ )
    {
        if( x == currPlyr )
        {
            for( y=0; y<gState->handCount[currPlyr]; y++ )
            {
                if(y==2)
                {
                    printf("\n   ");
                }
                printf(" %s",gState->hand[x][y]);
            }
        }
    }
    printf("  test end.\n");
}




int main() {

    int cardsAdd1,
        cardsAdd2,
        cardsGone1,
        cardsAdd2,
        choice1,
        choice2,
        currentPlayer = 0,
        handAmt = 0,
        cardHandPos,
        handMax = 5,
        numPlayers = 2,
        testRun = 0;
        

    int gameSeed = 555;

    srand (time(NULL));

    struct gameState origGame, scratchGame;

//
//  TEST SUMMARY
//
    printf( " - Init rand-test-card: minion - \n\n" );

    /* Init a Working Game */
	initializeGame( numPlayers, cds, gameSeed, &origGame );


    while( testRun < FUZZY_TIMES )
    {
        testRun++;

        /* work with a copy of the init'd game */
        memcpy( &scratchGame, &origGame, sizeof(struct gameState) );

        /* run card test */
        cardADVENTURER(game);
    }

    return 0;
}

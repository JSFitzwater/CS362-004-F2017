
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
#include <ctype.h>
#include <time.h>

#define FUZZY_TIMES 10
#define FUZZY_MAX 5

#define MAX_PLYR 2

#define GAME_START_DECK 10
#define NORM_TREASURE 2



int randNum( int iterations )
{
    /* StackOverflow. "Floating point exception (core     *
     *   dumped).In creator random numbers." Answer from  *
     *   user chux. Last modified April 23, 2017.         *
     * http:// stackoverflow.com/posts/43571595/revisions */

    int result;
    result = 1.0*rand()/RAND_MAX * iterations;
    return( result );
}



/** "Each of your opponents with at least one Copper in hand  **
 **     discards one Copper.                                  **
 **  Each of your opponents with no Coppers in hand reveals   **
 **     their hand to prove this.                             **/

void cardCUTPURSE( struct gameState *gS2)
{
    int randMinPlyrs,randMaxPlyrs,
        randMinHandCount,randMaxHandCount,
        cutpurseCard, outgoingCard,
        cpprDiscard, currPlyr, cardsRevealed;

    int v,w,x,y,z;
    v=w=x=y=z=cpprDiscard=cardsRevealed=0;

    currPlyr = whoseTurn(gS2);

    // ---


    randMaxPlyrs = randNum( gS2->numPlayers );
    randMinPlyrs = randNum( randMaxPlyrs );

    for( x = randMinPlyrs; x < randMaxPlyrs; x++ )
    {
        if( x != currPlyr )
        {

            randMaxHandCount = randNum( gS2->handCount[x] );
            randMinHandCount = randNum( randMaxHandCount );

            for( y = randMinHandCount; y < randMaxHandCount; y++ )
            {
                if( gS2->hand[x][y] == copper )
                {
                    cpprDiscard += 1;
                    discardCard(y, x, gS2, 0);
                    break;
                }

                if( y == gS2->handCount[x] )
                {
                    for( v = 0; v < gS2->handCount[x]; v++ )
                    {
                        if( gS2->hand[x][y] != copper )
                        {
                            cardsRevealed += 1;
                            printf("Player %d reveals card number %d\n", x, gS2->hand[x][v]);
                        }
                    }	
                    break;
                }		
            }
            
        }
            
    }				


    //discard randomly-held card from hand
    x=0;
    y=0;
    while( x )
    {
        while( y )
        {
            if( gS2->hand[x][y] == cutpurse )
            {
                cutpurseCard = gS2->hand[x][y];
                break;
            }
            y++;
        }
        x++;
    }

    outgoingCard = randNum( cutpurseCard );
    discardCard(outgoingCard, currPlyr, gS2, 0);


    // ---

    /* print current game state */

    printf( "outcome: CUTPURSE\n"
            "  check if curr plyr, start no - %d\n"
            "  check if curr plyr, end no  - %d\n"
            "  check if copper, start hand pos - %d\n"
            "  check if copper, end hand pos - %d\n"
            "  hand pos, cutpurse card - %d\n"
            "  hand pos, discarded card - %d\n",
            randMinPlyrs,randMaxPlyrs,
            randMinHandCount,randMaxHandCount,
            cutpurseCard, outgoingCard);

    printf("  test end.\n");
}




int main() {

    int numPlayers = 2,
        testRun = 0;

	int cds[10] = { adventurer, baron, village, cutpurse,
                    duchy, village, minion, sea_hag, 
                    smithy, village };
        

    int gameSeed = 555;

    srand (time(NULL));

    struct gameState origGame, gS;

//
//  TEST SUMMARY
//
    printf( " - Init rand-test-card: cutpurse - \n\n" );

    /* Init a Working Game */
	initializeGame( numPlayers, cds, gameSeed, &origGame );


//  while( testRun < FUZZY_TIMES )
    while( testRun < 1 )
    {
        testRun++;

        /* work with a copy of the init'd game */
        memcpy( &gS, &origGame, sizeof(struct gameState) );

        /* run card test */
        cardCUTPURSE(&gS);
    }

    return 0;
}


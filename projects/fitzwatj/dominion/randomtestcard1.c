
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

#define CARD_TYPES 10
#define CHOICES 2
#define TF_RANDCHOICES 1

#define MIN_HAND 0
#define MAX_HAND 5

#define MIN_PLYR 0
#define MAX_PLYR 2



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



void cardMINION( struct gameState gState )
{
	int cds[10] = { adventurer, baron, village, cutpurse,
                    duchy, village, minion, sea_hag, 
                    smithy, village };

    int cardHandPos, choice1,  
        choice2, currPlayer,
        p1discard, p1draw,
        pCount, rMN, rMX;

    int u, v,w,x,y,z;
    u=v=w=x=y=z=0;

    // ---

    /* replace players' hands with our tilted-test-deployment */

    for( x=MIN_PLYR; x<MAX_PLYR; x++ )
    {
        for( y=MIN_HAND; y<MAX_HAND; y++ )
        {
            // get a pseudorand num
            z = randNum( CARD_TYPES );
            if( z > (CARD_TYPES - 1) )
            {
                printf( "rand card types bust\n" );

                // assert( z < CARD_TYPES );
                if(z < CARD_TYPES)
                { printf("assert z < CARD_TYPES fail\n\n"); }
            }

            // grab that card
            gState.hand[x][y] = cds[z];
        }
    }


    /* check one of the cards-in-hand is Minion */

    for( x=MIN_PLYR; x<MAX_PLYR; x++ )
    {
        for( y=MIN_HAND; y<MAX_HAND; y++ )
        {
            // success. done.
            if( gState.hand[x][y] == minion )
            {
                currPlayer = x;
                cardHandPos = y;

                x = MAX_PLYR;
                y = MAX_HAND;

                break;
            }
        }
    }


    // ---

    gState.numActions++;

    // discard this card from hand
    discardCard( cardHandPos, currPlayer, &gState, 0 );


    // ---

    choice1 = randNum( CHOICES );
    if( choice1 > (CHOICES - 1) )
    {
        printf( "rand choices (1) bust\n" );

        // assert( choice1 < CHOICES );
        if(choice1 < CHOICES)
        { printf("assert choice1 < CHOICES fail\n\n"); }
    }


    /** this set by whether tester's toggled independent or **
     ** randomized-chance of testing minion's two possible  **
     ** outcomes (i.e., get gold or redraw)                 **/

    if( TF_RANDCHOICES )
    {
        choice2 = randNum( CHOICES );
        if( choice2 > (CHOICES - 1) )
        {
            printf( "rand choices (2) bust\n\n" );

            // assert( choice2 < CHOICES );
            if(choice2 < CHOICES)
            { printf("assert choice2 < CHOICES fail\n\n"); }

        }
    }
    // if not randomed, choice 2 takes alt of choice 1
    else {
        if( choice1 == 0 )
        {
            choice2 = 1;
        }
        else {
            choice2 = 0;
        }
    }


    // ---

    /* +2 coins */

    if( choice1 )		
    {
        u = gState.coins;
        gState.coins = gState.coins + randNum( 2 );
    }


    // ---

    /* discard hand, redraw 4, other players with 5+ cards *
     * discard hand and draw 4                             */

    if( choice2 )		
    {
        /* discard hand... rand min cards up to 5 */
        
        p1discard = (MAX_HAND - randNum( MAX_HAND ) );
        while( gState.handCount[currPlayer] > z )
        {
            discardCard( cardHandPos, currPlayer, &gState, p1discard );
        }

        /* re-draw hand... rand max cards up to 5 */
 
        p1draw = (MIN_HAND + randNum( MAX_HAND ) );
        for( x=0; x<p1draw; x++ )
        {
            drawCard( currPlayer, &gState );
        }

        /* opponent: if hand > 4, discard, re-draw... all modifiers rand */

        pCount = ( MIN_PLYR + randNum( MAX_PLYR ) );
        for( x=0; x<pCount; x++ )
        {
            if( x != currPlayer )
            {
                /* define 2 rand ints...                      *
                 * rMX eq rand-hand-MAX eq 1st rand num       *
                 * rMN eq rand-hand-MIN eq rMX - 2nd rand num */

                rMX = (MIN_HAND + (randNum( MAX_HAND ) - 1) );
                rMN = rMX - (MIN_HAND + (randNum( MAX_HAND ) - 1) );

                if(rMN < 0) // case: v's negative
                {
                    rMN = rMN*-1;
                }
                if(rMN > rMX) // case: v's larger than z
                {
                    w = rMN;
                    rMN = rMX;
                    rMX = w;
                }


                /* if hand size greater than... * 
                 * rand-hand-MAX, up to 4       */

                if( gState.handCount[x] > rMX )
                {
                    /* discard rand-num-MIN num of cards */

                    while( gState.handCount[x] > rMN )
                    {
                        discardCard( cardHandPos, x, &gState, rMN );
                    }
                        
                    /* re-draw rand-hand-MAX num of cards */

                    for( w=0; w<rMX; w++ )
                    {
                        drawCard( x, &gState );
                    }
                }
            }
        }
    }


    // ---

    /* print current game state */

    printf( "outcome: MINION\n  choice1 - %d\n  choice2 - %d\n"
            "  coins start - %d\n  coins end  - %d\n"
            "  p1 rand discard - %d\n  p1 rand draw - %d\n"
            "  rand player count - %d\n"
            "  p2 rand discard - %d\n  p2 rand draw - %d\n",
            choice1,choice2,u,gState.coins,p1discard,p1draw,
            pCount,rMN,rMX);

    printf("  p1\'s curr hand: ");
    for( x=0; x<MAX_PLYR; x++ )
    {
        if( x == currPlayer )
        {
            for( y=MIN_HAND; y<MAX_HAND; y++ )
            {
                if(y==2)
                {
                    printf("\n   ");
                }
                printf(" %d",gState.hand[x][y]);
            }
        }
    }

    printf("  p2\'s curr hand: ");
    for( x=0; x<MAX_PLYR; x++ )
    {
        if( x != currPlayer )
        {
            for( y=MIN_HAND; y<MAX_HAND; y++ )
            {
                if(y==2)
                {
                    printf("\n   ");
                }
                printf(" %d",gState.hand[x][y]);
            }
        }
    }
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

    struct gameState origGame, scratchGame;

//
//  TEST SUMMARY
//
    printf( " - Init rand-test-card: minion - \n\n" );

    /* Init a Working Game */
	initializeGame( numPlayers, cds, gameSeed, &origGame );


    while( testRun < 1 )
    {
        testRun++;

        /* work with a copy of the init'd game */
        memcpy( &scratchGame, &origGame, sizeof(struct gameState) );

        /* run card test */
        cardMINION(scratchGame);
    }

    return 0;
}

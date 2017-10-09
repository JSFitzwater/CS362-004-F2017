#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
// ***
int cardADVENTURER(int z, int cardDrawn, int *temphand, int drawntreasure, int currentPlayer,  struct gameState *state); 
int cardSMITHY(int i, int handPos, int currentPlayer,  struct gameState *state);
int cardMINION(int i, int j, int handPos, int currentPlayer, int choice1, int choice2,  struct gameState *state);
int cardCUTPURSE(int i, int j, int k, int handPos, int currentPlayer,  struct gameState *state);
int cardSEA_HAG(int i, int currentPlayer,  struct gameState *state); 
// ***
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

#endif

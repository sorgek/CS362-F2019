/*
** Name: Emily Sorg
** CS 362 Software Engineering II
** Final Project
** Description: UT For making sure playCard updates coins correctly
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){
    //initialize gameState
    printf("Bug 8\n");
    struct gameState *state = newTestState();
    int player = state->whoseTurn;

	//Add minion card to hand pos 0
    addCardToPlayersHand(state, minion, 0, player);
    state->coins = 0;

	//Play minion at position 0
    playCard(0, 1, 0, 0, state);
    safeAssert(state->coins == 2, "playCard function successfully updates coins when card to play is minion card with choice1=true");
    return 0;
}

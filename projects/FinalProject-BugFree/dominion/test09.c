/*
** Name: Emily Sorg
** CS 362 Software Engineering II
** Final Project
** Description: UT for tribute: Test opponent revealing two of same card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){
    //initialize gameState
    printf("Bug 9\n");

    struct gameState *state = newTestState();
    int player = state->whoseTurn;
    int player2 = state->whoseTurn + 1;

	//Add two smithies to opposing players hand
    addCardToPlayersHand(state, smithy, 0, player2);
    addCardToPlayersHand(state, smithy, 1, player2);
    state->numActions = 0;

    cardEffect(tribute, 0, 0, 0, state, 1, 0);
    safeAssert(state->numActions == 2, "When top two cards of opponents deck are smithies, tribute card adds 2 numActions");
    return 0;
}

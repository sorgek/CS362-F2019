/*
** Name: Emily Sorg
** CS 362 Software Engineering II
** Final Project
** Description: This unit test that coins from playcard are updated correclty
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){
    //initialize gameState

    struct gameState *state = newTestState();
    int player = state->whoseTurn;

    addCardToPlayersHand(state, minion, 0, player);

    state->coins = 0;

    //Play baron card
    playCard(0, 1, 0, 0, state);
    safeAssert(state->coins == 2, "playCard function successfully updates coins when card to play is minion card with choice1=true");
    return 0;
}

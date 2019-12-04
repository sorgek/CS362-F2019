/*
** Name: Emily Sorg
** CS 362 Software Engineering II
** Final Project
** Description: UT to test Happy path for Ambassador trash 2 card scenario
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){
    //initialize gameState
    printf("Bug 10\n");

    struct gameState *state = newTestState();
    int player = state->whoseTurn;

	//Set up hand with ambassador and 2 coppers
    addAllCards(state, estate, player);
    addSingleCardToHand(state, ambassador, 0);
    addSingleCardToHand(state, copper, 1);
    addSingleCardToHand(state, copper, 2);

    //call ambassador to discard 2 coppers with the first at pos 1

    safeAssert(cardEffect(ambassador, 1, 2, 0, state, 0, 0) == 0, "Ambassador card returns 0 when called with 2 cards.");
    return 0;
}

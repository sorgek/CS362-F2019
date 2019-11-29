/*
** Name: Ji Soo Yim
** CS 362 Software Engineering II
** Final Project
** Description: This unit test tests that the Tribute loop only iterates twice
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int main(){
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G, testG;
    int choice1, choice2, choice3, handPos, bonus;
    int card = tribute;
    int k[10] = {baron, minion, ambassador, tribute, mine, adventurer, village, smithy, estate, council_room};

    //initialize gameState
    initializeGame(numPlayers, k, seed, &G);

    //copy current gameState to a test gameState
    memcpy(&testG, &G, sizeof(struct gameState));

    //call Tribute
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, bonus);

    //assert test
    printf("Bug 7\n");
    printf("For loop in Tribute does not overrun: ");
    if((testG.numActions <= G.numActions + 4) && (testG.coins <= G.coins + 4) && (numHandCards(&testG) <= numHandCards(&G) + 2)){
        printf("PASSED\n");
    }else{
        printf("FAILED\n");
    }

    return 0;
}

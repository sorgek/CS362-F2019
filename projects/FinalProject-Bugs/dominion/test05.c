/*
** Name: Ji Soo Yim
** CS 362 Software Engineering II
** Final Project
** Description: This unit test tests the scoreFor function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int main(){
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 1;
    struct gameState G, testG;
    int k[10] = {baron, minion, ambassador, tribute, mine, adventurer, village, smithy, estate, council_room};

    //initialize gameState
    initializeGame(numPlayers, k, seed, &G);

    //copy current gameState to a test gameState
    memcpy(&testG, &G, sizeof(struct gameState));

    //set discard count so that score is 4
    G.discardCount[thisPlayer]

    //assert test
    printf("Bug 4\n");
    printf("isGameOver is true when 3 cards have supply count of 0: ");
    if(isGameOver(&G) == 1){
        printf("PASSED\n");
    }else{
        printf("FAILED\n");
    }

    return 0;
}


/*
** Name: Ji Soo Yim
** CS 362 Software Engineering II
** Final Project
** Description: This unit test tests the isGameOver function for number of loops
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int main(){
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G;
    int k[10] = {baron, minion, ambassador, tribute, mine, adventurer, village, smithy, estate, council_room};

    //initialize gameState
    initializeGame(numPlayers, k, seed, &G);

    //set supply count for the last 3 cards to be 0
    G.supplyCount[salvager] = 0;
    G.supplyCount[sea_hag] = 0;
    G.supplyCount[treasure_map] = 0;

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


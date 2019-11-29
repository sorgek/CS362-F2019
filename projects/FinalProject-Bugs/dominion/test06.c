/*
** Name: Ji Soo Yim
** CS 362 Software Engineering II
** Final Project
** Description: This unit test tests that Feast case logic is correct
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
    int card = feast;
    int k[10] = {baron, minion, ambassador, tribute, mine, adventurer, village, smithy, estate, council_room};

    //initialize gameState
    initializeGame(numPlayers, k, seed, &G);

    //copy current gameState to a test gameState
    memcpy(&testG, &G, sizeof(struct gameState));

    //call Feast
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, bonus);

    //assert test
    printf("Bug 6\n");
    printf("Feast does not increase coins directly: ");
    if(G.coins == testG.coins){
        printf("PASSED\n");
    }else{
        printf("FAILED\n");
    }

    return 0;
}

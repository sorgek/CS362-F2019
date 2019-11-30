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
    struct gameState G, testG;
    int k[10] = {baron, minion, ambassador, tribute, mine, adventurer, village, smithy, estate, council_room};

    //initialize gameState
    initializeGame(numPlayers, k, seed, &G);

    //copy current gameState to a test gameState
    memcpy(&testG, &G, sizeof(struct gameState));

    //set thisPlayer
    int thisPlayer = whoseTurn(&G);

    G.discardCount[thisPlayer] = 5;
    G.deckCount[thisPlayer] = 0;
    G.handCount[thisPlayer] = 0;

    //set all discard pile as province
    for(int i = 0; i < G.discardCount[thisPlayer]; i++){
        G.discard[thisPlayer][i] = estate;
    }

    //set all deck pile as estate
    for(int i = 0; i < G.deckCount[thisPlayer]; i++){
        G.deck[thisPlayer][i] = estate;
    }

     //set all hand pile as estate
    for(int i = 0; i < G.handCount[thisPlayer]; i++){
        G.hand[thisPlayer][i] = estate;
    }

    int testThisPlayer = whoseTurn(&testG);

    testG.discardCount[testThisPlayer] = 0;
    testG.deckCount[testThisPlayer] = 5;
    testG.handCount[testThisPlayer] = 0;

    //set all discard pile as estate
    for(int i = 0; i < testG.discardCount[testThisPlayer]; i++){
        testG.discard[testThisPlayer][i] = estate;
    }

    //set all deck pile as estate
    for(int i = 0; i < testG.deckCount[testThisPlayer]; i++){
        testG.deck[testThisPlayer][i] = province;
    }

     //set all hand pile as estate
    for(int i = 0; i < testG.handCount[testThisPlayer]; i++){
        testG.hand[testThisPlayer][i] = estate;
    }

    //assert test
    printf("Bug 5\n");
    printf("scoreFor function uses deckCount when analyzing deck cards: ");
    if(scoreFor(thisPlayer, &G) == scoreFor(testThisPlayer, &testG)){
        printf("PASSED\n");
    }else{
        printf("FAILED\n");
    }

    return 0;
}


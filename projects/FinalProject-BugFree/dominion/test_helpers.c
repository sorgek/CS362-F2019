#include "test_helpers.h"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

struct gameState* newTestState(){
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState *g = (struct gameState*)malloc(sizeof(struct gameState));
    memset(g,0,sizeof(struct gameState));

    initializeGame(2,k,1,g);

    return g;
}

struct gameState* refreshGameState(struct gameState* g){
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    memset(g,0,sizeof(struct gameState));
    initializeGame(2,k,1,g);

    return g;
}

int addCardToPlayersHand(struct gameState* game, int cardToAdd, int cardPos, int player){
    int currentCards = game->handCount[player];
    if(currentCards < cardPos + 1){
        int start;
        if(currentCards == 0) start = 0;
        else start = currentCards - 1;
        for(int i = start; i <= cardPos; i++){
            drawCard(player, game);
        }
    }
    game->hand[player][cardPos] = cardToAdd;

    return 0;
}


int addSingleCardToHand(struct gameState* game, int cardToAdd, int cardPos){
    return addCardToPlayersHand(game, cardToAdd, cardPos, game->whoseTurn);
}


int addAllCards(struct gameState* game, int cardToAdd, int player){

    int currentCards = game->handCount[player];

    for(int i = 0; i <= currentCards; i++){
        game->hand[player][i] = cardToAdd;
    }

    return 0;

}

int safeAssert(int eval, char* testName){

    if(eval){
		printf("%s: PASSED \n", testName);

	} else {
        printf("%s: FAILED\n", testName);
    }
    return 0;
}

int safeAssertForI(int eval, char* testName, int i){

    if(eval){

    } else {
        printf("FAILED for x = %i: %s \n", i, testName);
    }
    return 0;
}

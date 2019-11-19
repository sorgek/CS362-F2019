#include "testrandom.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "interface.h"

void randomizeAllHands(struct gameState* game){
	int numPlayers = game->numPlayers;
	for(int n = 0; n < numPlayers; n++){
		int numCards;
		if(rand() % 2 ==1 ){
			numCards = rand() % MAX_HAND;
		}else{
			numCards = 5; //Since you're usually gonna have 5 cards make more likely
		}

		game ->deckCount[n] = numCards;
		for(int i = 0; i < MAX_HAND; i++){
			if(i < numCards){
				game->hand[n][i] = rand() % 27; //random card
			}else{
				game->hand[n][i] = -1; //random card
				//no card
			}
		}
	}
}

void randomizeDiscard(struct gameState* game){
	int numPlayers = game->numPlayers;
	for(int n = 0; n < numPlayers; n++){
		int numCards;
		int randNum = rand() % 10;
		if(randNum == 0 ){
			numCards = 0;
		}else if(randNum == 1){
			numCards = 1;
		}else if(randNum == 2){
			numCards = MAX_HAND;
		}else{
			numCards = rand() % MAX_HAND;
		}

		game ->discardCount[n] = numCards;
		for(int i = 0; i < MAX_HAND; i++){
			if(i < numCards){
				game->discard[n][i] = rand() % 27; //random card
			}else{
				game->discard[n][i] = -1; //random card
				//no card
			}
		}
	}
}

int randomizeDeck(struct gameState* g){

	int numPlayers = g->numPlayers;
	for(int n = 0; n < numPlayers; n++){
		int numCards;
		int randNum = rand() % 10;
		if(randNum == 0 ){
			numCards = 0;
		}else if(randNum == 1){
			numCards = 1;
		}else if(randNum == 2){
			numCards = MAX_DECK;
		}else{
			numCards = rand() % MAX_DECK;
		}

		g->deckCount[n] = numCards;
		for(int i = 0; i < MAX_DECK; i++){
			if(i < numCards){
				g->deck[n][i] = rand() % 27; //random card
			}else{
				g->deck[n][i] = -1; //random card
				//no card
			}
		}
	}
}


struct gameState* newTestState(int numPlayers){

	if(numPlayers == 0) numPlayers = rand() % MAX_PLAYERS + 1;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState *g = (struct gameState*)malloc(sizeof(struct gameState));
	memset(g,0,sizeof(struct gameState));

	initializeGame(numPlayers,k,1,g);

	return g;
}

struct gameState* refreshGameState(struct gameState* g, int numPlayers){

	memset(g,0,sizeof(struct gameState));

	if(numPlayers == 0){
		numPlayers= rand() % MAX_PLAYERS;
		numPlayers++;
	}

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(numPlayers,k,1,g);

	randomizeAllHands(g);
	randomizeDiscard(g);
	randomizeDeck(g);

	return g;
}


void addCardToPlayersHand(struct gameState* game, int cardToAdd, int cardPos, int player){
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
}


int addSingleCardToHand(struct gameState* game, int cardToAdd, int cardPos){
	addCardToPlayersHand(game, cardToAdd, cardPos, game->whoseTurn);

	return 0;
}


int addAllCards(struct gameState* game, int cardToAdd, int player){

	int currentCards = game->handCount[player];

	for(int i = 0; i <= currentCards; i++){
		game->hand[player][i] = cardToAdd;
	}

	return 0;

}

int safeAssert(int eval, char* testName, struct gameState* g){

	if(eval){

	} else {
		printf("FAILED: %s \n", testName);
		printState(g);
	}
	return 0;
}

int safeAssertForI(int eval, char* testName, int i, struct gameState* g){

	if(eval){

	} else {
		printf("FAILED for x = %i: %s \n", i, testName);
		printState(g);
	}
	return 0;
}



#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>


int main() {

	int seed = 1000;
	int currentPlayer = 2;

	//declare the game state
	struct gameState G;

	// declare the card array
	int k[10] = { baron, minion, ambassador, tribute, mine, adventurer, village, smithy, estate, council_room };
	// set the game state
	memset(&G, 23, sizeof(struct gameState)); 

	// initialize a new game
	initializeGame(currentPlayer, k, seed, &G); 

	// Set up player 0's card
	G.hand[0][0] = remodel;
	G.hand[0][1] = duchy; 
	G.handCount[0] = 2;
	// Set player 0's discardCard pile to be empty
	G.discardCard[0][1] = -1;
	G.discardCard[0][0] = -1;
	G.Count[0] = 0;
	int cost;

	printf("start Bug 3\n")
	// Call cardEffect function
	cardEffect(remodel, 1, gold, 0, &G, 0, &cost);

	// Assert that one of the cards in the discardCard pile is a silver.
	

	if (assert(G.discardCard[0][0]) == gold) {
		printf("Passed\n");
	}
	else if (assert(G.discardCard[0][1] == gold)) {
		printf("Passed\n");
	}
	else {
		printf("Failed\n");
	}


	return 0;

}
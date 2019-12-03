#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>


int main() {
	int seed = 1000;
	int currentPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
	// declare the game state
	struct gameState G;

	printf("Bug 03\n");

	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(currentPlayer, k, seed, &G); // initialize a new game

	// Set up player 0's hand
	G.hand[0][0] = remodel;
	G.hand[0][1] = duchy;
	G.handCount[0] = 2;
	// Set player 0's discard pile to be empty
	G.discard[0][1] = -1;
	G.discard[0][0] = -1;
	G.discardCount[0] = 0;
	int coin_bonus;

	// Call cardEffect function
	cardEffect(remodel, 1, gold, 0, &G, 0, &coin_bonus);

	// Assert that one of the cards in the discardCard pile is a silver.
	

	if (G.discard[0][0] == gold) {
		printf("Passed\n");
	}
	else if (G.discard[0][1] == gold) {
		printf("Passed\n");
	}
	else {
		printf("Failed\n");
	}


	return 0;

}

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>

int main() {
	int seed = 1000;
	int currentPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
	// declare the game state
	struct gameState G;
	
	

	printf("Bug 01\n");

	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(currentPlayer, k, seed, &G); // initialize a new game

	// Get initial played card count 
	int initialPlayedCardCount = G.playedCardCount;
	// Add silver to player 0's hand
	G.hand[0][4] = silver;
	int coin_bonus;

	// Call cardEffect function
	cardEffect(mine, 4, gold, 0, &G, 0, &coin_bonus);

	// verify that your asserts pass, for the bugs your asserts may fail
	// playedCardCount should only go up by 1, which is the mine card being played
	if (initialPlayedCardCount + 1== G.playedCardCount) {
		printf("Passed\n");
	}
	else {
		printf("Failed\n");
	}

	return 0;
}
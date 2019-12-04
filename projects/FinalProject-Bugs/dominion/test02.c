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


	printf("Bug 02\n");

	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(currentPlayer, k, seed, &G); // initialize a new game

	// Set up player 0's hand
	G.handCount[0] = 2;
	G.hand[0][0] = mine;
	G.hand[0][1] = copper;
	int coin_bonus;

	// Call cardEffect function
	cardEffect(mine, 1, gold, 0, &G, 0, &coin_bonus);

	// Neither of the cards in the player's hand should be gold

	if (G.hand[0][0] != gold) {
		if (G.hand[0][1] != gold) {
			printf("Can trash copper and gain gold: PASSED\n");
		}
		else {
			printf("Can't trash copper and gain gold: FAILED\n");
		}
	}
	else {
		printf("Can't trash copper and gain gold: FAILED\n");
	}

	return 0;
}
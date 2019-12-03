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
	printf("start Bug 1\n");
	//initialize gameState
	initializeGame(currentPlayer, k, seed, &G);
	
	int handPos = G.cardCount;
	//set the first player's hand is silver count
	G.hand[0][4] = silver;
	int cost;
	cardEffect(mine, 4, gold, 0, &G, 0, &cost);
	
	//see if the cardeffect can work under the handPos +1=cost;

	if (assert(handPos+1=G.cost)) {
		printf("Passed\n");
		
	}
	else {
		printf("Failed\n");

	}
	
	return 0;

}
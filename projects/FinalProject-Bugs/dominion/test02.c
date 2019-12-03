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
	struct gameState testG;

	// declare the card array
	int k[10] = { baron, minion, ambassador, tribute, mine, adventurer, village, smithy, estate, council_room };

	//initialize gameState
	initializeGame(currentPlayer, k, seed, &G);
	testG->hand[currentPlayer][choice1] + 3;
	//set handPos to 0;
	G.count[choice1] = 0;
	G.count[choice2] = 0;
	G.count[treasure_map] = 0;
	G.count[curse] = 0;


	//assert test
	printf("start Bug 2\n");

	//see if the cardeffect can work under the handPos is 0;

	if (getCost(&G)>getCost(&testG)){
		printf("Passed\n");
	}
	else {
		printf("Failed\n");

	}

	return 0;

}
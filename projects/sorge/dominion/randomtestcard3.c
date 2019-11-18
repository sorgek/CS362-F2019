#include "randomtestcard1.h"
#include "tributecard.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testrandom.h"

int main(){

	int TRIALS = 100;
	struct gameState *game = newTestState(2);

	printf("\n\nSTARTING TESTS FOR TRIBUTE************\n\n");

	
	//No neg paths for tribute
	//HAPPY PATH: ALL PATHS!  based on randomness.
	for (int t = 0; t < TRIALS; t++) {
		refreshGameState(game, 2);

		printf("TRIAL %i \n", t);

		game->numActions = rand() % 1025;
		game->coins = rand() % 1025;

		//Set random players

		int numPlayers = game->numPlayers;
		printf("Using numPlayers: %i\n", numPlayers);

		int p = rand() % numPlayers;
		int p2 = p + 1;
		if(p2 >=game->numPlayers) p = 0;
		printf("Using p: %i and p2: %i \n", p, p2);


		int handCount = game->handCount[p];
		int numActions = game->numActions;
		int numCoins = game->coins;

		int p2DeckCount = game->deckCount[p2];
		int p2HandCount = game->handCount[p2];
		int p2DiscardCount = game->discardCount[p2];

		int numGold = 0;
		int numVictory = 0;
		int numAction = 0;


		//Count up number of cards;
		for(int i =0; i < 2; i++){
			int card = game->hand[p2][i];
			if (card == copper || card == silver || card == gold) { //Treasure cards
				numGold += 2;
			}else if(card == estate || card == duchy || card ==province){
				numVictory += 2;
			}else if(card != -1){
				numAction += 2;
			}
		}

		safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP returns 0", game);
		safeAssert(game->coins == numCoins + numGold * 2, "Tribute HP: 2 gold gotten for each treasure", game);
		safeAssert(game->numActions == numActions + numAction * 2, "Tribute HP: 2 actions for each Action card", game);
		safeAssert(game->handCount[p] == handCount + numVictory * 2, "Tribute HP: 2 cards for each victory card", game);
		safeAssert(game->handCount[p2] == p2HandCount - 2, "Tribute HP: 2 gold card revealed - P2 handCount decreases by 2", game);
	}

	free(game);
}
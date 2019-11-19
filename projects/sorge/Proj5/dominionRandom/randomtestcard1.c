#include "randomtestcard1.h"
#include "minioncard.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testrandom.h"

int main(){

	int TRIALS = 100;
	printf("\n\nSTARTING TESTS FOR BARON************\n\n");

	struct gameState *game = newTestState(0);
	refreshGameState(game, 0);

	for (int t = 0; t < TRIALS * 10; t++) {
		int player = 0;
		//HAPPY/NEG PATH: DiscardEstate = true
		int handCount = game->handCount[player];

		game->numBuys = rand() % 1025;
		game->coins = rand() % 1025;

		int numCoins = game->coins;
		int numBuys = game->numBuys;
		int handSize = game->handCount[player];
		int hasEstate = 0;

		for(int i = 0; i < handSize; i++){
			if (game->hand[player][i] == estate){
				hasEstate = 1;
			}
		}

		safeAssert(baronCard(1, game, player) == 0, "Verify baronCard discardEstate=true happy path returns 0", game);

		if(hasEstate == 1){
			safeAssert(game->numBuys == numBuys + 1, "Verify baron discardEstate=true happy path grants extra buy", game);
			safeAssert(game->coins == numCoins + 4, "Verify baron discardEstate=true happy path grants 4 extra coins", game);
			safeAssert(game->handCount[player] == handCount - 1, "Verify baron discardEstate=true discards estate & decreases handCount", game);

		}else{
			//NEG PATH : NO ESTATE
			safeAssert(game->numBuys == numBuys, "Verify baron discardEstate=true no estate NEG PATH doesn't increase buys", game);
			safeAssert(game->coins == numCoins, "Verify baron discardEstate=true no estate NEG PATH doesn't grant extra coins", game);
			safeAssert(game->handCount[player] == handCount, "Verify baron discardEstate=true: NEG PATH no estate does not discard ccard", game);
		}

		refreshGameState(game, 0);
	}


	for (int t = 0; t < TRIALS; t++) {
		//HAPPY/NEG PATH: DiscardEstate = false - gain estate

		int player = 0;

		int handCount = game->handCount[player];

		game->numBuys = rand() % 1025;
		game->coins = rand() % 1025;

		int numCoins = game->coins;
		int numBuys = game->numBuys;
		int handSize = game->handCount[player];

		int hasEstateBefore = 0;
		for(int i = 0; i < handSize; i++){
			if (game->hand[player][i] == estate){
				hasEstateBefore = 1;
			}
		}

		safeAssert(baronCard(0, game, player) == 0, "Verify baronCard discardEstate=true happy path returns 0", game);

		int hasEstateAfter = 0;
		handSize = game->handCount[player];

		for(int i = 0; i < handSize; i++){
			if (game->hand[player][i] == estate){
				hasEstateAfter = 1;
			}
		}
		safeAssert(game->numBuys == numBuys + 1, "Verify baron discardEstate=false happy path grants extra buy", game);
		safeAssert(game->coins == numCoins, "Verify baron discardEstate=false happy path does not add coins", game);
		safeAssert(hasEstateBefore == hasEstateAfter, "Verify baron discardEstate=false happy path does not discard estate in hand", game);
		safeAssert(game->discard[player][game->discardCount[player] - 1] == estate, "Verify baron discardEstate=false happy gains an estate", game);

		refreshGameState(game, 0);
	}

	free(game);

}
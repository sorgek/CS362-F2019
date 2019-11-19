#include "randomtestcard1.h"
#include "minioncard.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testrandom.h"

int main(){

	int TRIALS = 100;

	printf("\n\nSTARTING TESTS FOR MINION************\n\n");

	struct gameState *game = newTestState(0);
	int p = game->whoseTurn;

	for (int t = 0; t < TRIALS; t++) {
		//Happy path - gainTwoGold true gains us gold and one action
		game->numActions = rand() % 1025;
		game->coins = rand() % 1025;

		int numCoins = game->coins;
		int numActions = game->numActions;

		safeAssert(minionCard(p, 1, 1, game, 0) == 0, "Verify minion gainTwoGold=true happy path returns 0", game);
		safeAssert(game->numActions == numActions + 1,
				   "Verify minion gainTwoGold=true happy path increases numActions", game);
		safeAssert(game->coins == numCoins + 2, "Verify minion gainTwoGold=true happy path increases coins by 2", game);

		refreshGameState(game, 0);
	}


	for (int t = 0; t < TRIALS; t++) {
		//Happy path - gainTwoGold true gains us gold and one action
		game->numActions = rand() % 1025;
		game->coins = rand() % 1025;

		int numCoins = game->coins;
		int numActions = game->numActions;
		int handLength[4] = {0, 0, 0, 0};
		for (int np = 0; np < game->numPlayers; np++) {
			handLength[np] = game->handCount[np];
		}

		safeAssert(minionCard(p, 0, 1, game, 0) == 0, "Verify minion gainTwoGold=false happy path returns 0", game);
		safeAssert(game->numActions == numActions + 1,
				   "Verify minion gainTwoGold=false happy path increases numActions", game);
		safeAssert(game->coins == numCoins,
				   "Verify minion gainTwoGold=false happy path does not increase coins by 2", game);


		//verify hand state
		for (int i = 0; i < game->numPlayers; i++) {
			int hasRightNumCards;
			if (handLength[i] > 3) {
				hasRightNumCards = game->handCount[i] == 4;
			} else if (handLength[i] < 4) {
				hasRightNumCards = game->handCount[i] == handLength[i];
			} else {
				hasRightNumCards = 0;
			};

			safeAssertForI(hasRightNumCards, "Verify minion gainTwoGold=false happy path reduces hand count to 4 for player X", i, game);
			if (!hasRightNumCards) printf("Hand state: Hand count for player %i = %i\n", i, game->handCount[i]);
		}

		refreshGameState(game, 0);
	}

}

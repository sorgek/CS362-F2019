#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "refactoredcards.h"
#include "dominion_helpers.h"


int main(){
	testBaron();
	testMinion();
	testTribute();
	testAmbassador();
	testMine();
	return 0;
}

struct gameState* newTestState(){
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState *g = (struct gameState*)malloc(sizeof(struct gameState));
	memset(g,0,sizeof(struct gameState));

	initializeGame(2,k,1,g);

	return g;
}

struct gameState* refreshGameState(struct gameState* g){
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	memset(g,0,sizeof(struct gameState));
	initializeGame(2,k,1,g);

	return g;
}

int addCardToPlayersHand(struct gameState* game, int cardToAdd, int cardPos, int player){
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
}


int addAllCards(struct gameState* game, int cardToAdd, int player){

	int currentCards = game->handCount[player];

	for(int i = 0; i <= currentCards; i++){
		game->hand[player][i] = cardToAdd;
	}

}

int safeAssert(int eval, char* testName){

	if(eval){

	} else {
		printf("FAILED: %s \n", testName);
	}
	return 0;
}

int safeAssertForI(int eval, char* testName, int i){

	if(eval){

	} else {
		printf("FAILED for x = %i: %s \n", i, testName);
	}
	return 0;
}

int testBaron() {

	printf("\n\nSTARTING TESTS FOR BARON************\n\n");

	struct gameState *game = newTestState();
	int player = game->whoseTurn;

	//NEG PATH: card fails if discardEstate choice is selected but they don't have any Estates
	addAllCards(game, copper, player);
	safeAssert(baronCard(1, game, player) == -1, "Verify baron returns -1 if discardEstate=true and no estates are in hand");
	addSingleCardToHand(game, estate, 0);
	safeAssert(game->discard[player][game->discardCount[player] - 1] == estate, "Verify baron discardEstate=false happy gains an estate");

	refreshGameState(game);

	//HAPPY PATH: DiscardEstate = true
	int handCount = game->handCount[player];

	game->numBuys = 0;
	game->coins = 0;
	safeAssert(baronCard(1, game, player) == 0, "Verify baronCard discardEstate=true happy path returns 0");
	safeAssert(game->numBuys == 1, "Verify baron discardEstate=true happy path grants extra buy");
	safeAssert(game->coins == 4, "Verify baron discardEstate=true happy path grants 4 extra coins");
	safeAssert(game->hand[player][0] == -1, "Verify baron discardEstate=true happy path discards estate");
	safeAssert(game->handCount[player] == handCount - 1, "Verify baron discardEstate=true discards estate & decreases handCount");

	refreshGameState(game);

	//HAPPY PATH: DiscardEstate = false - gain estate
	game->numBuys = 0;
	game->coins = 0;
	addAllCards(game, copper, player);
	addSingleCardToHand(game, estate, 0);
	safeAssert(baronCard(0, game, player) == 0, "Verify baronCard discardEstate=false happy path returns 0");
	safeAssert(game->numBuys == 1, "Verify baron discardEstate=false happy path grants extra buy");
	safeAssert(game->coins == 0, "Verify baron discardEstate=false happy path does not add coins");
	safeAssert(game->hand[player][0] == estate, "Verify baron discardEstate=false happy path does not discard estate in hand");
	safeAssert(game->discard[player][game->discardCount[player] - 1] == estate, "Verify baron discardEstate=false happy gains an estate");

	free(game);

	return 0;
}

int testMinion(){

	struct gameState *game = newTestState();
	int p = game->whoseTurn;

	printf("\n\nSTARTING TESTS FOR MINION************\n\n");

	//Happy path - gainTwoGold true gains us gold and one action
	game->numActions = 0;
	game->coins = 0;
	safeAssert(minionCard(p, 1, 1, game, 0) == 0, "Verify minion gainTwoGold=true happy path returns 0");
	safeAssert(game->numActions == 1, "Verify minion gainTwoGold=true happy path increases numActions");
	safeAssert(game->coins == 2, "Verify minion gainTwoGold=true happy path increases coins by 2");

	refreshGameState(game);

	//Happy path - gainTwoGold=false gains one action, 4 new cards for all players
	game->numActions = 0;
	game->coins = 0;

	//place card not in play in players hands so we can test that they drew new hands
	for(int i = 0; i < game->numPlayers; i++) {
		if(game->handCount[i] < 5){
			for(int h = game->handCount[i]; h <= 5; h++){
				drawCard(i, game);
			}
		}
		addAllCards(game, steward, i);
	}

	int discardCount = 	game->discardCount[p];
	int handCount = game->handCount[p];

	safeAssert(minionCard(p, 0, 1, game, 0) == 0, "Verify minion gainTwoGold=false happy path returns 0");
	safeAssert(game->numActions == 1, "Verify minion gainTwoGold=false happy path increases numActions");
	safeAssert(game->coins == 0, "Verify minion gainTwoGold=false happy path does not increase coins by 2");

	//verify hand state
	for(int i = 0; i < game->numPlayers; i++) {
		int hasRightNumCards = game->handCount[i] == 4;
		safeAssertForI(hasRightNumCards,
				   "Verify minion gainTwoGold=false happy path reduces hand count to 4 for player X", i);
		if(!hasRightNumCards) printf("Hand state: Hand count for player %i = %i\n", i, game->handCount[i]);
		if (game->handCount[i] == 4) {
			safeAssertForI(game->hand[i][1] != steward && game->hand[i][0] != steward && game->hand[i][2] != steward &&
					   game->hand[3][1] != steward,
					   "Verify minion gainTwoGold=false happy path has players redraw hands for player X", i);
		}
	}

	//Verif hand states
	for(int i = 0; i <= 4; i++) {
		refreshGameState(game); //reinitialize gameState to reduce interference with previous tests
		game->handCount[1] = i;
		safeAssertForI(minionCard(p, 1, 1, game, 0) == 0, "Verify minion gainTwoGold=false happy path does not let "
				"players with <X cards draw: gamestate is still workable", i);
		safeAssertForI(game->handCount[1] == i,
				   "Verify minion gainTwoGold=false happy path does not let players with <X cards draw", i);
	}

	free(game);
	return 0;
}



int testAmbassador(){

	printf("\n\nSTARTING TESTS FOR AMBASSADOR************\n\n");

	struct gameState *game = newTestState();
	int p = game->whoseTurn;

	//HAPPY PATH: numToDiscard=0 & 1 & 2 -> we do not hit supply = 0;
	for(int numToDiscard =0; numToDiscard <= 2; numToDiscard++){
		game->supplyCount[copper] = 10;
		int copperSupply = game->supplyCount[copper];
		addAllCards(game, estate, p);
		addSingleCardToHand(game, ambassador, 0);
		addSingleCardToHand(game, copper, 1);
		if(numToDiscard == 2) addSingleCardToHand(game, copper, 2);

		safeAssertForI(copperSupply >= game->numPlayers + numToDiscard, "Ambassador HP: numToDiscard=X set up correctly", numToDiscard);
		safeAssertForI(ambassadorCard(p, 1, numToDiscard, game, 0) == 0, "Ambassador HP: numToDiscard=X returns 0", numToDiscard);
		safeAssertForI(copperSupply == copperSupply - game->numPlayers + numToDiscard , "Ambassador HP: numToDiscard=X supplyCount ends up correct", numToDiscard);

		//players got card
		for(int pNum = 0; pNum < game->numPlayers; pNum++){
			int discardSize = game->discardCount[pNum];
			int recievedCopyOfCard = game->discard[pNum][discardSize-1] == copper;
			safeAssertForI(recievedCopyOfCard, "Ambassador HP: numToDiscard=X gave out the card to a player", numToDiscard);

		}
		refreshGameState(game);
	}

	//HAPPY PATH: numToDiscard = 1 and supply hitss zero
	//I'm not going to write this one now because this is a lot of work for one tiny edge case and I have two midterms, two quizzes, two assignments, and a full time job this week

	//NEG PATH: numToDiscard > 2
	addAllCards(game, estate, p);
	safeAssert(ambassadorCard(p, 1, 3, game, 0) == -1, "Ambassador Neg Path: numToDiscard=3 returns -1");

	refreshGameState(game);

	//NEG PATH: toDiscard == thisCardHandPos
	addAllCards(game, estate, p);
	addSingleCardToHand(game, ambassador, 0);
	safeAssert(ambassadorCard(p, 1, 1, game, 1) == -1, "Ambassador Neg Path: toDiscard == thisCardHandPos card returns -1");

	refreshGameState(game);

	//NEG PATH: numToDiscard > # of that type of card we're holding
	addAllCards(game, estate, p);
	addSingleCardToHand(game, ambassador, 0);
	addSingleCardToHand(game, copper, 1);
	safeAssert(ambassadorCard(p, 1, 2, game, 0) == -1, "Ambassador Neg Path: numToDiscard > # of that type of card we're holding returns -1");

	free(game);
	return 0;
}


int testTribute(){

	printf("\n\nSTARTING TESTS FOR TRIBUTE************\n\n");

	//WHY DID I PICK THIS CARD THIS IS THE WORST
	struct gameState *game = newTestState();
	int p = game->whoseTurn;
	int p2 = p+1;

	//HAPPY PATH: 2 gold card revealed
	int handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	addCardToPlayersHand(game, copper, 0, p2);
	addCardToPlayersHand(game, copper, 1, p2);
	game->handCount[p2] = 2;
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: 2 gold card revealed returns 0");
	safeAssert(game->coins == 4, "Tribute HP: 2 gold card revealed gain 4 coins");
	safeAssert(game->numActions == 0, "Tribute HP: 2 gold card revealed numActions no change");
	safeAssert(game->handCount[p] == handCount, "Tribute HP: 2 gold card revealed - P1 handCount no change");
	safeAssert(game->handCount[p2] == 0, "Tribute HP: 2 gold card revealed - P2 handCount = 0");

	refreshGameState(game);

	//HAPPY PATH: 1 treasure, 1 action card revealed
	handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	addCardToPlayersHand(game, copper, 0, p2);
	addCardToPlayersHand(game, smithy, 1, p2);
	game->handCount[p2] = 2;
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: 1 treasure, 1 action card revealed returns 0");
	safeAssert(game->coins == 2, "Tribute HP: 1 treasure, 1 action card revealed gain 2 coins");
	safeAssert(game->numActions == 2, "Tribute HP: 1 treasure, 1 action card revealed gain 2 actions");
	safeAssert(game->handCount[p] == handCount, "Tribute HP: 1 treasure, 1 action card revealed - P1 handCount no change");
	safeAssert(game->handCount[p2] == 0, "Tribute HP: 1 treasure, 1 action card revealed - P2 handCount = 0");

	refreshGameState(game);

	//HAPPY PATH: 2 action cards revealed
	handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	addCardToPlayersHand(game, smithy, 0, p2);
	addCardToPlayersHand(game, smithy, 1, p2);
	game->handCount[p2] = 2;
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: 2 action cards  revealed returns 0");
	safeAssert(game->coins == 0, "Tribute HP: 1 treasure, 2 action cards revealed coins no change");
	safeAssert(game->numActions == 4, "Tribute HP: 2 action cards revealed gain 4 actions");
	safeAssert(game->handCount[p] == handCount, "Tribute HP: 2 action cards revealed handCount - P1 no change");
	safeAssert(game->handCount[p2] == 0, "Tribute HP:2 Action cards revealed - P2 handCount = 0");

	refreshGameState(game);


	//HAPPY PATH: 1 Action  1 Victory card revealed
	handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	game->handCount[p2] = 2;
	addCardToPlayersHand(game, smithy, 0, p2);
	addCardToPlayersHand(game, estate, 1, p2);
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: 1 Action 1 Victory card revealed returns 0");
	safeAssert(game->coins == 0, "Tribute HP: 1 Action  1 Victory card revealed coins no change");
	safeAssert(game->numActions == 4, "Tribute HP: 1 Action  1 Victory card revealed +4 actions");
	safeAssert(game->handCount[p] == handCount + 2, "Tribute HP: 1 Action 1 Victory card +2 to P1 handCount");
	safeAssert(game->handCount[p2] == 0, "Tribute HP:1 Action 1 Victory card revealed - P2 handCount = 0");

	refreshGameState(game);

	//HAPPY PATH: 2 Victory cards revealed
	handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	game->handCount[p2] = 2;
	addCardToPlayersHand(game, estate, 0, p2);
	addCardToPlayersHand(game, estate, 1, p2);
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: 2 Victory cards revealed returns 0");
	safeAssert(game->coins == 0, "Tribute HP: 2 Victory cards revealed coins no change");
	safeAssert(game->numActions == 0, "Tribute HP: 2 Victory cards revealed actions no change");
	safeAssert(game->handCount[p] == handCount + 4, "Tribute HP: 2 Victory cards revealed - +4 to P1 handCount");
	safeAssert(game->handCount[p2] == 0, "Tribute HP: 2 Victory cards revealed - P2 handCount = 0");

	refreshGameState(game);

	//Skip 1 action 1 gold since I believe it's already covered

	//HAPPY PATH: P2 only has 1 treasure card
	handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	game->handCount[p2] = 1;
	addCardToPlayersHand(game, copper, 0, p2);
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: P2 only has 1 treasure card returns 0");
	safeAssert(game->coins == 2, "Tribute HP: P2 only has 1 treasure card- +2 coins");
	safeAssert(game->numActions == 0, "Tribute HP: 2 Victory cards revealed - no change to actions");
	safeAssert(game->handCount[p] == handCount, "Tribute HP: 2 Victory cards revealed - no change to P1 handCount");
	safeAssert(game->handCount[p2] == 0, "Tribute HP: 2 Victory cards revealed - P2 handCount = 0");

	refreshGameState(game);

	//HAPPY PATH: P2 has no cards
	handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	game->handCount[p2] = 0;
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: P2 has no cards returns 0");
	safeAssert(game->coins == 2, "Tribute HP: P2 has no cards - no change to numActions");
	safeAssert(game->numActions == 0, "Tribute HP: P2 has no cards - actions no change to numActions");
	safeAssert(game->handCount[p] == handCount + 4, "Tribute HP: P2 has no cards - no change to P1 handCount");
	safeAssert(game->handCount[p2] == 0, "Tribute HP: P2 has no cards - no change P2 tohandCount");

	refreshGameState(game);

	//HAPPY PATH: P2 has no cards
	handCount = game->handCount[p];
	game->numActions = 0;
	game->coins = 0;
	game->handCount[p2] = 0;
	safeAssert(tributeCard(p, p2, game) == 0, "Tribute HP: P2 has no cards returns 0");
	safeAssert(game->coins == 2, "Tribute HP: P2 has no cards - no change to numActions");
	safeAssert(game->numActions == 0, "Tribute HP: P2 has no cards - actions no change to numActions");
	safeAssert(game->handCount[p] == handCount + 4, "Tribute HP: P2 has no cards - no change to P1 handCount");
	safeAssert(game->handCount[p2] == 0, "Tribute HP: P2 has no cards - no change P2 tohandCount");

	refreshGameState(game);

	//TODO: Test when discard and deck count are less than 1

	free(game);
	return 0;
}

int testMine(){
	struct gameState *game = newTestState();
	int p = game->whoseTurn;
	int handcount = game->handCount[p];
	printf("\n\nSTARTING TESTS FOR MINE************\n\n");

	//HAPPY PATH: trash copper get silver
	addSingleCardToHand(game, copper, 0);
	safeAssert(mineCard(p, 0, silver, game, 0) == 0, "Mine HP: trash copper get silver - returns 0");
	safeAssert(game->discard[p][game->discardCount[p] -1] == silver, "Mine HP: trash copper get silver - gained card");
	safeAssert(game->handCount[p] == handcount -1, "Mine HP: trash copper get silver - card is discarded");

	refreshGameState(game);

	//HAPPY PATH: trash silver get gold
	addSingleCardToHand(game, silver, 0);
	safeAssert(mineCard(p, 0, gold, game, 0) == 0, "Mine HP: trash silver get gold - returns 0");
	safeAssert(game->discard[p][game->discardCount[p] -1] == gold, "Mine HP: trash silver get gold - gained card");
	safeAssert(game->handCount[p] == handcount -1, "Mine HP: trash silver get gold- card is discarded");

	refreshGameState(game);

	//HAPPY PATH: trash silver get silver
	addSingleCardToHand(game, silver, 0);
	safeAssert(mineCard(p, 0, silver, game, 0) == 0, "Mine HP: trash silver get silver - returns 0");
	safeAssert(game->discard[p][game->discardCount[p] -1] == silver, "Mine HP: trash silver get silver - gained card");
	safeAssert(game->handCount[p] == handcount -1, "Mine HP: trash silver get silver- card is discarded");

	refreshGameState(game);

	//NEG PATH: trash copper get gold
	addSingleCardToHand(game, copper, 0);
	safeAssert(mineCard(p, 0, gold, game, 0) == -1, "Mine NEG: trash copper get gold - returns -1");
	safeAssert(game->discard[p][game->discardCount[p] -1] != gold, "Mine NEG: copper silver get gold - gained card");
	safeAssert(game->handCount[p] == handcount , "Mine NEG: trash copper get gold- card is not discarded");

	refreshGameState(game);

	//NEG PATH: trash non-treasure guard get silver
	addSingleCardToHand(game, mine, 0);
	safeAssert(mineCard(p, 0, silver, game, 0) == -1, "Mine NEG: trash non-treasure get silver - returns -1");
	safeAssert(game->discard[p][game->discardCount[p] -1] != silver, "Mine NEG: trash non-treasure get silver - gained card");
	safeAssert(game->handCount[p] == handcount, "Mine NEG: trash non-treasure get silver- card is not discarded");

	refreshGameState(game);

	//NEG PATH: trash silver get non-treasure
	addSingleCardToHand(game, silver, 0);
	safeAssert(mineCard(p, 0, mine, game, 0) == -1, "Mine NEG: trash silver get non-treasure - returns -1");
	safeAssert(game->discard[p][game->discardCount[p] -1] != mine, "Mine NEG: trash silver get non-treasure - gained card");
	safeAssert(game->handCount[p] == handcount, "Mine NEG: trash silver get non-treasure - card is not discarded");
	refreshGameState(game);

	free(game);

	return 0;
}

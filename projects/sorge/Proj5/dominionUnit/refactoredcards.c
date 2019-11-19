#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int mineCard(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos){
	int i = 0;
	int j = 0;

	j = state->hand[currentPlayer][choice1];  //store card we will trash

	if (state->hand[currentPlayer][choice1] < curse || state->hand[currentPlayer][choice1] > gold)
	{
		/*
		INSERT BUG:
		change state->hand[currentPlayer][choice1] < curse  to	state->hand[currentPlayer][choice1] < copper
		*/
		return -1;
	}

	if (choice2 > treasure_map || choice2 < curse)
	{
		return -1;
	}

	if ((getCost(state->hand[currentPlayer][choice1]) + 6) > getCost(choice2))
	{
		/*
		INSERTED BUG£º

		change +3 to +6
		so by discard copper we can get gold( but in correct way, discard a copper can only get silver)
		*/
		return -1;
	}

	gainCard(choice2, state, 2, currentPlayer);

//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

//discard trashed card
	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == j)
		{
			discardCard(i, currentPlayer, state, 0);
			break;
		}
	}

	return 0;
}

int tributeCard(int currentPlayer, int nextPlayer, struct gameState *state){

	int tributeRevealedCards[2] = {-1, -1};
	int i;

	if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
		if (state->deckCount[nextPlayer] > 0) {
			tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
			state->deckCount[nextPlayer]--;
		}
		else if (state->discardCount[nextPlayer] > 0) {
			tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer] - 1];
			state->discardCount[nextPlayer]--;
		}
		else {
			//No Card to Reveal
			if (DEBUG) {
				printf("No cards to reveal\n");
			}
		}
	}

	else {
		if (state->deckCount[nextPlayer] == 0) {
			for (i = 0; i < state->discardCount[nextPlayer]; i++) {
				state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
				state->deckCount[nextPlayer]++;
				state->discard[nextPlayer][i] = -1;
				state->discardCount[nextPlayer]--;
			}

			shuffle(nextPlayer, state);//Shuffle the deck
		}
		tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
		state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
		state->deckCount[nextPlayer]--;
		tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
		state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
		state->deckCount[nextPlayer]--;
	}

	if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
		state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
		state->playedCardCount++;
		tributeRevealedCards[1] = -1;
	}

	for (i = 0; i <= 2; ++i) {
		/*
		Inserted BUG:
		change i++ to ++i;
		so instead of rotate 3 times,it will rotate 2 times

		*/
		if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver ||
			tributeRevealedCards[i] == gold) { //Treasure cards
			state->coins += 1;

			/*
			Inserted BUG:
			change state-> coins+=2; to state->coins+=1;


			*/
		} else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy ||
				   tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens ||
				   tributeRevealedCards[i] == great_hall) { //Victory Card Found
			drawCard(currentPlayer, state);
			drawCard(currentPlayer, state);
		} else { //Action Card
			state->numActions = state->numActions + 2;
		}
	}

	return 0;
}


int ambassadorCard(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos){

	int i = 0;

	int j = 0;		//used to check if player has enough cards to discard
	if (choice2 > 2 || choice2 < 0)
	{
		return -1;
	}

	if (choice1 == handPos)
	{
		return -1;
	}

	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
		{
			++j;
			/*
			INSERT BUG:
			change j++ to ++j;
			so the rotate time is changed

			*/
		}
	}
	if (j > choice2)
	{
		/*
		INSERT BUG:
		change j< choice2 to j> choice2

		*/
		return -1;
	}

	if (DEBUG)
		printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

//increase supply count for choosen card by amount being discarded
	state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

//each other player gains a copy of revealed card
	for (i = 0; i < state->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			gainCard(state->hand[currentPlayer][choice1], state, 0, i);
		}
	}

//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);

//trash copies of cards returned to supply
	for (j = 0; j < choice2; j++)
	{
		for (i = 0; i < state->handCount[currentPlayer]; i++)
		{
			if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
			{
				discardCard(i, currentPlayer, state, 1);
				break;
			}
		}
	}

	return 0;
}

int minionCard(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos){

	int i;//+1 action
	int j =0;
	state->numActions++;
 //discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	if (choice1)
	{
		state->coins = state->coins + 1;
		/*
		Insert BUG: state->coins+2 change to state->coins+1

		*/
	}
	else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
	{
		//discard hand
		while (numHandCards(state) > 0)
		{
			discardCard(handPos, currentPlayer, state, 0);
		}

		//draw 4
		for (i = 0; i < 4; ++i)
			/*
			Inserted BUG:
			change i++ to ++i
			then it will rotate 4 times instead of 3 times

			*/
		{
			drawCard(currentPlayer, state);
		}

		//other players discard hand and redraw if hand size > 4
		for (i = 0; i < state->numPlayers; i++)
		{
			if (i != currentPlayer)
			{
				if (state->handCount[i] > 4)
				{
					//discard hand
					while (state->handCount[i] > 0)
					{
						discardCard(handPos, i, state, 0);
					}

					//draw 4
					for (j = 0; j < 4; j++)
					{
						drawCard(i, state);
					}
				}
			}
		}

	}
	return 0;
}


int baronCard(int choice1, struct gameState *state, int currentPlayer){
	state->numBuys++;//Increase buys by 1!
	if (choice1 > 0) { //Boolean true or going to discard an estate
		int p = 1;//Iterator for hand!
		/*
		Inserted BUG:
		p=0 change to p=1;
		let p start with 1, then it iretator have wrong times

		*/
		int card_not_discarded = 1;//Flag for discard set!
		while (card_not_discarded) {
			if (state->hand[currentPlayer][p] == estate) { //Found an estate card!
				state->coins += 0;//Add 4 coins to the amount of coins

				/*
				Inserted BUG:
				state->coins +=4 change to state->coins +=0;
				this will result this card have no any usage.


				*/
				state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
				state->discardCount[currentPlayer]++;
				for (; p < state->handCount[currentPlayer]; p++) {
					state->hand[currentPlayer][p] = state->hand[currentPlayer][p + 1];
				}
				state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
				state->handCount[currentPlayer]--;
				card_not_discarded = 0;//Exit the loop
			}
			else if (p > state->handCount[currentPlayer]) {
				if (DEBUG) {
					printf("No estate cards in your hand, invalid choice\n");
					printf("Must gain an estate if there are any\n");
				}
				if (supplyCount(estate, state) > 0) {
					gainCard(estate, state, 0, currentPlayer);

					state->supplyCount[estate]--;//Decrement estates
					if (supplyCount(estate, state) == 0) {
						isGameOver(state);
					}
				}
				card_not_discarded = 0;//Exit the loop
			}

			else {
				p++;//Next card
			}
		}
	}

	else {
		if (supplyCount(estate, state) > 0) {
			gainCard(estate, state, 0, currentPlayer);//Gain an estate

			state->supplyCount[estate]--;//Decrement Estates
			if (supplyCount(estate, state) == 0) {
				isGameOver(state);
			}
		}
	}
	return 0;
}




#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int mineCard(int currentPlayer, int choiceToTrashPos, int choiceCardToGain, struct gameState *state, int handPos){

	int j = state->hand[currentPlayer][choiceToTrashPos];  //store card we will trash

	if (state->hand[currentPlayer][choiceToTrashPos] < copper || state->hand[currentPlayer][choiceToTrashPos] > gold)
	{
		return -1;
	}

	if (choiceCardToGain > treasure_map || choiceCardToGain < estate)
	{
		printf("TACO CAT");

		return -1;
	}

	int costOfTrash = (getCost(state->hand[currentPlayer][choiceToTrashPos]) + 4);
	int costOfGain = getCost(choiceCardToGain);
	if ( (getCost(state->hand[currentPlayer][choiceToTrashPos]) + 4) > getCost(choiceCardToGain) )
	{
		printf("%i !> %i", costOfTrash, costOfGain);
		return -1;
	}

	gainCard(choiceCardToGain, state, 2, currentPlayer);

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	//discard trashed card
	for (int i = 0; i < state->handCount[currentPlayer]; i++)
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
			tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
			state->deckCount[nextPlayer]--;
		}
		else if (state->discardCount[nextPlayer] > 0) {
			tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
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

			shuffle(nextPlayer,state);//Shuffle the deck
		}
		tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
		state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
		//state->deckCount[nextPlayer]--;
		tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
		state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
		state->deckCount[nextPlayer]--;
	}

	if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
		state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
		state->playedCardCount++;
		tributeRevealedCards[1] = -1;
	}

	for (i = 0; i <= 2; i ++) {
		if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
			state->coins += 2;
		}

		else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
			drawCard(currentPlayer, state);
//            drawCard(currentPlayer, state);
		}
		else { //Action Card
			state->numActions = state->numActions + 2;
		}
	}

	return 0;
}


int ambassadorCard(int currentPlayer, int toDiscard, int numToDiscard, struct gameState *state, int thisCardHandPos){


	int j = 0;		//used to check if player has enough cards to discard
	int i;

	if (numToDiscard > 2 || numToDiscard < 0)
	{
		return -1;
	}

	if (toDiscard == thisCardHandPos)
	{
		return -1;
	}

	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (i != thisCardHandPos && i == state->hand[currentPlayer][toDiscard] /*&& i != toDiscard*/)
		{
			j++;
		}
	}
	if (j < numToDiscard)
	{
		return -1;
	}

	if (DEBUG)
		printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][toDiscard]);

	//increase supply count for chosen card by amount being discarded
	state->supplyCount[state->hand[currentPlayer][toDiscard]] += numToDiscard;

	//each other player gains a copy of revealed card
	for (i = 0; i < state->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			gainCard(state->hand[currentPlayer][toDiscard], state, 0, i);
		}
	}

	//discard played card from hand
	discardCard(thisCardHandPos, currentPlayer, state, 0);

	//trash copies of cards returned to supply
	for (j = 0; j < numToDiscard; j++)
	{
		for (i = 0; i < state->handCount[currentPlayer]; i++)
		{
			if (state->hand[currentPlayer][i] == state->hand[currentPlayer][toDiscard]) {
				discardCard(i, currentPlayer, state, 0);
				break;
			}
		}
	}

	return 0;
}

int minionCard(int currentPlayer, int gainTwoGold, int choiceDiscard, struct gameState *state, int handPos){

	int i;

	//+1 action
	state->numActions++;

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	if (gainTwoGold) {
		state->coins = state->coins + 3;

	} else if (choiceDiscard)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
	{
		//discard hand
		while(numHandCards(state) > 0)
		{
			discardCard(handPos, currentPlayer, state, 0);
		}

		//draw 4
		for (i = 0; i < 4; i++)
		{
			drawCard(currentPlayer, state);
		}

		//other players discard hand and redraw if hand size > 4
		for (i = 0; i < state->numPlayers; i++)
		{
			if (i != currentPlayer)
			{
//                if ( state->handCount[i] > 4 )
//                {
				//discard hand
				while( state->handCount[i] > 0 )
				{
					discardCard(handPos, i, state, 0);
				}

				//draw 4
				for (int j = 0; j < 4; j++)
				{
					drawCard(i, state);
				}
//                }
			}
		}

	}

	return 0;
}


int baronCard(int discardEstate, struct gameState *state, int currentPlayer){

	state->numBuys++;//Increase buys by 1!
	if (discardEstate > 0) { //Boolean true or going to discard an estate
		int p = 0;//Iterator for hand!
		int card_not_discarded = 1;//Flag for discard set!
		while(card_not_discarded) {
			if (state->hand[currentPlayer][p] == estate) { //Found an estate card!
				state->coins += 4;//Add 4 coins to the amount of coins
				state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
				state->discardCount[currentPlayer]++;
				for (; p < state->handCount[currentPlayer]; p++) {
					state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
				}
//                state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
				state->handCount[currentPlayer]--;
				card_not_discarded = 0;//Exit the loop
			}
			else if (p > state->handCount[currentPlayer]) {
				if(DEBUG) {
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


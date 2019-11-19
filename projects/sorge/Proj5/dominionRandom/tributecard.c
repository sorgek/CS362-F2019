#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


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
#ifndef DOMINION_REFACTOREDCARDS_H
#define DOMINION_REFACTOREDCARDS_H


int mineCard(int currentPlayer, int choiceToTrashPos, int choiceCardToGain, struct gameState *state, int handPos);
int tributeCard(int currentPlayer, int nextPlayer, struct gameState *state);
int ambassadorCard(int currentPlayer, int toDiscard, int numToDiscard, struct gameState *state, int thisCardHandPos);
int minionCard(int currentPlayer, int gainTwoGold, int choiceDiscard, struct gameState *state, int handPos);
int baronCard(int discardEstate, struct gameState *state, int currentPlayer);

#endif //DOMINION_REFACTOREDCARDS_H

#ifndef DOMINION_REFACTOREDCARDS_H
#define DOMINION_REFACTOREDCARDS_H


int mineCard(int, int, int, struct gameState *state, int handPos);
int tributeCard(int, int, struct gameState *state);
int ambassadorCard(int, int, int, struct gameState *, int);
int minionCard(int, int, int, struct gameState *, int);
int baronCard(int, struct gameState *, int);

#endif //DOMINION_REFACTOREDCARDS_H

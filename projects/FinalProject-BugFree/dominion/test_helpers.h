#ifndef PROJECTS_TEST_HELPERS_H
#define PROJECTS_TEST_HELPERS_H

struct gameState* newTestState();
struct gameState* refreshGameState(struct gameState* g);
int addCardToPlayersHand(struct gameState* game, int cardToAdd, int cardPos, int player);
int addSingleCardToHand(struct gameState* game, int cardToAdd, int cardPos);
int addAllCards(struct gameState* game, int cardToAdd, int player);
int safeAssert(int eval, char* testName);
int safeAssertForI(int eval, char* testName, int i);

#endif //PROJECTS_TEST_HELPERS_H

//
// Created by sal on 11/17/19.
//

#ifndef DOMINION_RANDOMTEST_H
#define DOMINION_RANDOMTEST_H

#include "testrandom.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include "baroncard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "interface.h"

void randomizeAllHands(struct gameState* game);
void randomizeDiscard(struct gameState* game);
int randomizeDeck(struct gameState* g);
struct gameState* newTestState(int numPlayers);
struct gameState* refreshGameState(struct gameState* g, int numPlayers);
void addCardToPlayersHand(struct gameState* game, int cardToAdd, int cardPos, int player);
int addSingleCardToHand(struct gameState* game, int cardToAdd, int cardPos);
int addAllCards(struct gameState* game, int cardToAdd, int player);
int safeAssert(int eval, char* testName, struct gameState* g);
int safeAssertForI(int eval, char* testName, int i, struct gameState* g);

#endif //DOMINION_RANDOMTEST_H

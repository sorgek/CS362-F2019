//
// Created by sal on 11/7/19.
//

#ifndef DOMINION_TESTCARDS_H
#define DOMINION_TESTCARDS_H


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <printf.h>
#include <stdio.h>
#include <malloc.h>



struct gameState* newTestState();
struct gameState* refreshGameState(struct gameState* g);

int addAllCards(struct gameState* game, int cardToAdd);
int addSingleCardToHand(struct gameState* game, int cardToAdd, int cardPos);
int addCardToPlayersHand(struct gameState* game, int cardToAdd, int cardPos, int player);
int addSingleCardToHand(struct gameState* game, int cardToAdd, int cardPos);

int safeAssert(int eval, char* testName);
int safeAssertForI(int eval, char* testName, int i);

int testBaron();
int testMinion();
int testAmbassador();
int testTribute();
int testMine();

#endif //DOMINION_TESTCARDS_H

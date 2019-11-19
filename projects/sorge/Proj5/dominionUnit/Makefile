CFLAGS= -Wall -fpic --coverage -lm -std=c99 -lgcov  -fprofile-arcs -ftest-coverage -O0

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

refactoredcards.o: refactoredcards.c refactoredcards.h dominion_helpers.h
	gcc -c refactoredcards.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c refactoredcards.o rngs.o
	gcc -c dominion.c -g $(CFLAGS)

testcards: testcards.c dominion.o refactoredcards.o rngs.o
	gcc -o testcards testcards.c -g rngs.o dominion.o refactoredcards.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittestresults: testcards
	./testcards &> unittestresult.out
	gcov -b -c refactoredcards.c >> unittestresult.out
	cat refactoredcards.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe testcards  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

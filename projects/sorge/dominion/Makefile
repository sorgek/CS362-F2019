CFLAGS= -Wall -fpic --coverage -lm -std=c99 -lgcov  -fprofile-arcs -ftest-coverage -O0

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

baroncard.o: baroncard.h baroncard.c
	gcc -c baroncard.c -g  $(CFLAGS)

minioncard.o: minioncard.h minioncard.c
	gcc -c minioncard.c -g  $(CFLAGS)

tributecard.o: tributecard.h tributecard.c
	gcc -c tributecard.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c tributecard.o baroncard.o minioncard.o rngs.o
	gcc -c dominion.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testrandom.o: dominion.o testrandom.c rngs.o minioncard.o
	gcc -c testrandom.c -g $(CFLAGS)


#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o testrandom.o interface.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o testrandom.o minioncard.o baroncard.o tributecard.o interface.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o testrandom.o interface.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o testrandom.o minioncard.o baroncard.o tributecard.o interface.o rngs.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o testrandom.o interface.o
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o testrandom.o minioncard.o baroncard.o tributecard.o interface.o rngs.o $(CFLAGS)

randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
	rm -f randomtestresults.out
	./randomtestcard1
	./randomtestcard2
	./randomtestcard3
	gcov -b -f baroncard.c >> randomtestresults.out
	gcov -b -f minioncard.c >> randomtestresults.out
	gcov -b -f tributecard.c >> randomtestresults.out
	cat baroncard.c.gcov >> randomtestresults.out
	cat minioncard.c.gcov >> randomtestresults.out
	cat tributecard.c.gcov >> randomtestresults.out


runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

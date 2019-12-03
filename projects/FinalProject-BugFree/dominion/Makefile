CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

test_helpers.o: test_helpers.h test_helpers.c dominion.o
	gcc -c test_helpers.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

test01: test01.c dominion.o rngs.o
	gcc -o test01 -g test01.c dominion.o rngs.o $(CFLAGS)

test02: test02.c dominion.o rngs.o
	gcc -o test02 -g test02.c dominion.o rngs.o $(CFLAGS)

test03: test03.c dominion.o rngs.o
	gcc -o test03 -g test03.c dominion.o rngs.o $(CFLAGS)

test04: test04.c dominion.o rngs.o
	gcc -o test04 -g test04.c dominion.o rngs.o $(CFLAGS)

test05: test05.c dominion.o rngs.o
	gcc -o test05 -g test05.c dominion.o rngs.o $(CFLAGS)

test06: test06.c dominion.o rngs.o
	gcc -o test06 -g test06.c dominion.o rngs.o $(CFLAGS)

test07: test07.c dominion.o rngs.o
	gcc -o test07 -g test07.c dominion.o rngs.o $(CFLAGS)

test08: test08.c test_helpers.o dominion.o rngs.o
	gcc -o test08 -g test08.c dominion.o rngs.o test_helpers.o $(CFLAGS)

test09: test09.c test_helpers.o dominion.o rngs.o
	gcc -o test09 -g test09.c dominion.o rngs.o test_helpers.o $(CFLAGS)

test10: test10.c test_helpers.o dominion.o rngs.o
	gcc -o test10 -g test10.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest: test10
	./test10

unittestresults: test01 test02 test03 test04 test05 test06 test07 test08 test09 test10
	./test01 >> unittestresults.out
	./test02 >> unittestresults.out
	./test03 >> unittestresults.out
	./test04 >> unittestresults.out
	./test05 >> unittestresults.out
	./test06 >> unittestresults.out
	./test07 >> unittestresults.out
	./test08 >> unittestresults.out
	./test09 >> unittestresults.out
	./test10 >> unittestresults.out

	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe test01 test02 test03 test04 test05 test06 test07 test08 test09 test10

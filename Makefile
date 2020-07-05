COMPILER = g++
CFLAGS = -O3 -static
PRE_CFLAGS = ${CFLAGS} -c
TARGET = PCWS

CLEAN = clean
CLEANUP = cleanup

all: ${CLEANUP} MersenneRng ResultTuple WeightedMinHash ${TARGET} ${CLEAN}

MersenneRng: mersenne_rng.h mersenne_rng.cpp
	${COMPILER} ${PRE_CFLAGS} mersenne_rng.cpp -o mersenne_rng.o

ResultTuple: ResultTuple.h ResultTuple.cpp
	${COMPILER} ${PRE_CFLAGS} ResultTuple.cpp -o ResultTuple.o

WeightedMinHash: WeightedMinHash.h WeightedMinHash.cpp
	${COMPILER} ${PRE_CFLAGS} WeightedMinHash.cpp -o WeightedMinHash.o

${TARGET}: main.cpp
	${COMPILER} ${CFLAGS} main.cpp *.o -o ${TARGET}
	rm -rf *~
	rm -rf *.o

${CLEAN}:
	rm -rf *~
	rm -rf *.o

${CLEANUP}: ${CLEAN}
	rm -rf ${TARGET}
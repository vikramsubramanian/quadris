CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = quadris
OBJECTS = game.o levels.o gameBoard.o BlockFactory.o IBlock.o JBlock.o LBlock.o OBlock.o SBlock.o ZBlock.o TBlock.o block.o Command.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
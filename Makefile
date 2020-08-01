CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = quadris
OBJECTS = main.o game.o levels.o gameBoard.o Command.o BlockFactory.o IBlock.o JBlock.o LBlock.o OBlock.o SBlock.o ZBlock.o TBlock.o block.o TextDisplay.o subject.o observer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
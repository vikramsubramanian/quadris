CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = quadris
OBJECTS = main.o game.o levels.o gameBoard.o BlockFactory.o blockTypes.o  block.o Command.o TextDisplay.o subject.o observer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
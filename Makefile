CXX = g++
CXXFLAGS = -std=c++14 -MMD
EXEC = quadris
OBJECTS = game.o levels.o gameBoard.o command.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
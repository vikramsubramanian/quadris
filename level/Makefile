CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = main
OBJECTS = levels.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: test

test:
	make -f Makefile.test

.PHONY: test_clean

test_clean:
	make -f Makefile.test clean
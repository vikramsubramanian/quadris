CXX = g++
CXXFLAGS = -Wall -MMD -g
OBJS =   block.o TBlock.o ZBlock.o SBlock.o OBlock.o LBlock.o JBlock.o IBlock.o  BlockFactory.o blockmain.o gameBoard.o
DEPENDS = ${OBJS:.o=.d}
EXEC = factory

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -rf ${DEPENDS} ${OBJS} ${EXEC}

-include ${DEPENDS}
CC=/opt/local/bin/clang-mp-19
CXX=/opt/local/bin/clang++-mp-19
RM=rm -f
CPPFLAGS=-g -O3 -std=c++23
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp Puzzles.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

BUILD=$(CXX) $(LDFLAGS) -o puzzles $(OBJS) $(LDLIBS)

$(info $$BUILD = $(BUILD))

all: puzzles

puzzles: $(OBJS)
	$(CXX) $(LDFLAGS) -o puzzles $(OBJS) $(LDLIBS)

main.o: main.cpp Puzzles.h iostreamext.h geometry_utils.h SimpleLinkedList.h Puzzle01Part1Data.h Puzzle02Part1Data.h Puzzle03Part1Data.h Puzzle04Part1Data.h 
	$(CXX) $(CPPFLAGS) -c main.cpp

Puzzles.o: Puzzles.cpp Puzzles.h iostreamext.h
	$(CXX) $(CPPFLAGS) -c Puzzles.cpp

#mattp1part2.o: mattp1part2.cpp mattp1part2.h Puzzle01Part1Data.h
#	$(CXX) $(CPPFLAGS) -c mattp1part2.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) puzzles

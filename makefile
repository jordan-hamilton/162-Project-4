# Source: http://web.engr.oregonstate.edu/~rookert/cs162/03.mp4

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = main.o Menu.o Barbarian.o BlueMen.o Character.o Game.o HarryPotter.o Medusa.o Vampire.o
SRCS = main.cpp Menu.cpp Barbarian.cpp BlueMen.cpp Character.cpp Game.cpp HarryPotter.cpp Medusa.cpp Vampire.cpp
HEADERS = Menu.hpp Barbarian.hpp BlueMen.hpp Character.hpp Game.hpp HarryPotter.hpp Medusa.hpp Vampire.hpp

project3: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o project3

$(OBJS): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $(@:.o=.cpp)

clean:
	rm *.o project3

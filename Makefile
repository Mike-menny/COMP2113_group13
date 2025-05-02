CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lstdc++fs
TARGET = game
OBJS = main.o registerUser.o library.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: main.cpp registerUser.h library.h
	$(CXX) $(CXXFLAGS) -c main.cpp

registerUser.o: registerUser.cpp registerUser.h
	$(CXX) $(CXXFLAGS) -c registerUser.cpp

library.o: library.cpp library.h
	$(CXX) $(CXXFLAGS) -c library.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 
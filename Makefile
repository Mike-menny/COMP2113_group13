CXXFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cpp library.cpp registerUser.cpp save.cpp load.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	g++ $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 
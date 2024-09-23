CXX := g++

CXXFLAGS := -std=c++11 -Wall -Werror -Wextra -pedantic -O3 -IC:/path/to/SFML/include	# For Windows Users: Enter the Path to the SFML/include directory like following: -IC:/path/to/SFML/include
SFMLFLAGS := -LC:/path/to/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system		# For Windows Users: Enter the Path to the SFML/lib directory like following: -LC:/path/to/SFML/lib

TARGET := main

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFMLFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

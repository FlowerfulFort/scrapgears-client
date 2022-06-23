CXX=g++
FLAGS=-std=c++17 -Wall -lpthread -I./include

BIN=main
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:$(DIREC_SRC)/%.cpp=$(DIREC_OBJ)/%.o)
DIREC_OBJ=obj
DIREC_SRC=src

all: $(OBJ)
	$(CXX) $(FLAGS) -o $(BIN) $^

$(DIREC_OBJ)/%.o: $(DIREC_SRC)/%.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -f obj/*.o
	rm $(BIN)



CC=clang
CFLAGS=-g -Wall

RM=del /f /q /s

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BIN=wordle.exe

all: $(BIN)

release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJ) $(OBJS)
	$(RM) *.exe
	$(CC) $(CFLAGS) $(OBJS) -o $@ -luser32
	$(RM) *.ilk *.pdb

$(OBJ)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir $@

$(BINDIR):
	mkdir $@

clean:
	cls
	$(RM) *.exe
	$(RM) $(OBJ)\*

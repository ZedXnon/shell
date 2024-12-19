SRC = src/main.c
CFLAGS = -Wall -Werror -Wextra -pedantic
CC = gcc
BUILD = build/test
BIN = bin
OBJ = $(BIN)/$(notdir $(SRC:.c=.o))

$(shell mkdir -p $(BIN) build)

all: $(BUILD)

$(BUILD): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILD)

$(BIN)/%.o: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $@

clean:
	rm -f $(OBJ) $(BUILD)

.PHONY: all clean test install
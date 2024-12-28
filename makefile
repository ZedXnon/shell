SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), \
    main.c \
    utills.c \
	commands.c \
)
CFLAGS = -Wall -Werror -Wextra -pedantic
CC = gcc
BUILD = build/test
BIN = bin
OBJ = $(patsubst $(SRC_DIR)%.c,$(BIN)/%.o,$(SRC))

$(shell mkdir -p $(BIN) build)

all: $(BUILD)

$(BUILD): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILD)

$(BIN)/%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BUILD)

.PHONY: all clean test install
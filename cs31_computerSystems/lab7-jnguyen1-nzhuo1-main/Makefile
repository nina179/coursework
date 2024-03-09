CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable

TARGET = stringtester

LIB = my_strings.o

SRC = $(TARGET).c

all: $(TARGET)

$(TARGET): $(SRC) $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIB)

$(LIB): my_strings.c my_strings.h
	$(CC) $(CFLAGS) -c my_strings.c

clean:
	$(RM) $(TARGET) $(LIB)

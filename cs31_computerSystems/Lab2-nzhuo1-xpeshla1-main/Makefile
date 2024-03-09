#
# Swarthmore College, CS 31
# Copyright (c) 2023 Swarthmore College Computer Science Department,
# Swarthmore PA
#

# This makefile uses some variables to specify the
# compiler, the flags to the compiler:

CC = gcc

CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable


all: datarep

datarep: datarep.c
	$(CC) $(CFLAGS) -o datarep datarep.c

clean:
	$(RM) datarep

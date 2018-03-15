#############################################################################
#  COSC2138/CPT220 - Programming Principles 2A
# SP2 2015 Assignment #2 - word link program
# Full Name        : Timothy Boye
# Student Number   : s3482043
# 
# Start up code provided by the C Teaching Team
#############################################################################

# Student ID
USER = s3482043

# Compiler
CC = gcc

# Coompiler flags
CFLAGS = -Wall -pedantic -ansi

# C preprocessor flags
CPFLAGS = 

# LD flags
LDFLAGS = 

# Source files
SRC = wordlink.c wordlink_utility.c wordlink_options.c list.c game.c
SRC_H = $(SRC:.c=.h)

# Object files
OBJ = $(SRC:.c=.o)

# Executable filename
EXE = wordlink

# Default rule
all: $(EXE)

# Link the program
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXE)

# compile c files
%.o: %.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $<

# Zip up the source
archive:
	zip $(USER)-a2.zip $(SRC) $(SRC_H) makefile readme.txt

# clean
clean:
	rm -f $(EXE) $(OBJ)


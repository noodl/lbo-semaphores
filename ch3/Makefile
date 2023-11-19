CC = gcc
CFLAGS = -pthread

# Get the list of all .c files in the current directory
SRCS = $(wildcard *.c)

# Generate the list of corresponding executable names without extension
EXECS = $(SRCS:.c=)

all: $(EXECS)

# Rule to build each executable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECS)

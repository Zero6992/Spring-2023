CC=gcc
CFLAGS=-DONLINE_JUDGE -O2 -w -fmax-errors=3 -std=c11 -lm
TARGET=test

all: $(TARGET)

$(TARGET): test.c
	$(CC) $(CFLAGS) test.c -o $(TARGET)

clean:
	rm -f $(TARGET)

# ./check_ans /Users/zero6992/Documents/Spring-2023/Algorithms/hw01/hw0103.c
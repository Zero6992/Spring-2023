CC=gcc
CFLAGS=-DONLINE_JUDGE -O2 -w -fmax-errors=3 -std=c11 -lm
TARGET=test

all: $(TARGET)

$(TARGET): test.c
	$(CC) $(CFLAGS) test.c -o $(TARGET)

clean:
	rm -f $(TARGET)

# ./check_ans /home/zero/Documents/Algo/test.c
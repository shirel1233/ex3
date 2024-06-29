CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = StrList

all: $(TARGET)

$(TARGET): StrList.o Main.o
	$(CC) $(CFLAGS) -o $(TARGET) StrList.o Main.o

StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c StrList.c

Main.o: Main.c StrList.h
	$(CC) $(CFLAGS) -c Main.c

clean:
	rm -f *.o $(TARGET)

BIN_PATH = ./bin
INSTALL_PATH = /usr/local/bin
INCLUDE_PATH = ../include
CC:=gcc

CFLAGS:=-g -Wall
PROG = i2libisoff

all: main.o i2libisoff.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG) main.o i2libisoff.o
main.o: main.c i2libisoff.o
	$(CC) $(CFLAGS) -c main.c
i2libisoff.o: i2libisoff.c i2libisoff.h $(INCLUDE_PATH)/i2context.h
	$(CC) $(CFLAGS) -c i2libisoff.c
install:
	cp $(BIN_PATH)/$(PROG) $(INSTALL_PATH)
clean:
	rm -f $(BIN_PATH)/$(PROG) main.o i2libisoff.o
unistall:
	rm -f $(BIN_PATH)/$(PROG) main.o i2libisoff.o $(INSTALL_PATH)/$(PROG)

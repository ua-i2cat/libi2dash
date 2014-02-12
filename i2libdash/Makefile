BIN_PATH = ./bin
INSTALL_PATH = /usr/local/bin
CC:=gcc

CFLAGS:=-g -Wall
PROG = i2libdash

all: main.o i2libdash.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG) main.o i2libdash.o
main.o: main.c i2libdash.o
	$(CC) $(CFLAGS) -c main.c i2libdash.o
i2libdash.o: i2libdash.c i2libdash.h
	$(CC) $(CFLAGS) -c i2libdash.c
install:
	cp $(BIN_PATH)/$(PROG) $(INSTALL_PATH)
clean:
	rm -f $(BIN_PATH)/$(PROG) main.o i2libdash.o
unistall:
	rm -f $(BIN_PATH)/$(PROG) main.o i2libdash.o $(INSTALL_PATH)/$(PROG)
BIN_PATH = ./bin
INSTALL_PATH = /usr/local/bin
LIBISOFF_PATH = ../i2libisoff
LIBIDASH_PATH = ../i2libdash
INCLUDE_PATH = ../include
CC:=gcc

CFLAGS:=-g -Wall
PROG = i2libdash

all: main.o i2libdash.o $(LIBISOFF_PATH)/i2libisoff.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG) main.o i2libdash.o $(LIBISOFF_PATH)/i2libisoff.o $(INCLUDE_PATH)/h264_stream.o
main.o: main.c i2libdash.o 
	$(CC) $(CFLAGS) -c main.c
i2libdash.o: i2libdash.c i2libdash.h $(INCLUDE_PATH)/h264_stream.o $(INCLUDE_PATH)/i2context.h
	$(CC) $(CFLAGS) -c i2libdash.c
h264_stream.o: h264_stream.c h264_stream.h bs.h
	cd $(INCLUDE_PATH)
	$(CC) $(CFLAGS) -c h264_stream.c
	cd $(LIBIDASH_PATH)
install:
	cp $(BIN_PATH)/$(PROG) $(INSTALL_PATH)
clean:
	rm -f $(BIN_PATH)/$(PROG) main.o i2libdash.o $(INCLUDE_PATH)/h264_stream.o
unistall:
	rm -f $(BIN_PATH)/$(PROG) main.o i2libdash.o $(INSTALL_PATH)/$(PROG) $(INCLUDE_PATH)/h264_stream.o

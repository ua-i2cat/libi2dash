BIN_PATH = ./bin
LIB_PATH = ./lib
SRC_PATH = ./src
TEST_PATH = ./test
DIR_PATH = ../
INCLUDE_PATH = ./include
INSTALL_PATH = /usr/local/bin
INSTALL_LIB_PATH = /usr/local/lib
INSTALL_INCLUDE_PATH = /usr/local/include
CC =g++
LDFLAGS = -fPIC -shared
CFLAGS = -Wall -ggdb -fPIC
PROG_ISOFF = isofftest
PROG_I2DASH = i2dashtest
PROG_V_LIB = i2libtest_video
PROG_A_LIB = i2libtest_audio
PROG_PAPER = paper
VERSION = 1.0.0
LIB_SHARED_NAME = libi2dash.so
LIB_STATIC_NAME = libi2dash.a
TEST_DIR = /tmp/pruebas
ISOFF_SEGMENT = isoff
I2DASH_SEGMENT = i2dash
LIB_SEGMENT = i2lib
LIB_FLAGS = -li2dash

all: testing

testing: isoff_test.o i2dash_test.o
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG_ISOFF) $(TEST_PATH)/isoff_test.o i2libisoff.o
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG_I2DASH) $(TEST_PATH)/i2dash_test.o i2libdash.o i2libisoff.o i2nalparser.o h264_stream.o
	mkdir -p $(TEST_DIR)/$(ISOFF_SEGMENT)
	mkdir -p $(TEST_DIR)/$(I2DASH_SEGMENT)

i2dash_test.o:  $(TEST_PATH)/i2dash_test.c i2libdash.o h264_stream.o i2nalparser.o i2libisoff.o
	$(CC) $(CFLAGS) -c $(TEST_PATH)/i2dash_test.c
	mv i2dash_test.o $(TEST_PATH)/

i2libdash.o: $(SRC_PATH)/i2libdash.c $(INCLUDE_PATH)/i2libdash.h i2nalparser.o h264_stream.o i2libisoff.o
	$(CC) $(CFLAGS) -c $(SRC_PATH)/i2libdash.c

i2nalparser.o: $(SRC_PATH)/i2nalparser.c $(INCLUDE_PATH)/i2nalparser.h
	$(CC) $(CFLAGS) -c $(SRC_PATH)/i2nalparser.c

h264_stream.o: $(SRC_PATH)/h264_stream.c $(INCLUDE_PATH)/h264_stream.h $(INCLUDE_PATH)/bs.h
	$(CC) $(CFLAGS) -c $(SRC_PATH)/h264_stream.c

isoff_test.o: $(TEST_PATH)/isoff_test.c i2libisoff.o
	$(CC) $(CFLAGS) -c $(TEST_PATH)/isoff_test.c
	mv isoff_test.o $(TEST_PATH)/

i2libisoff.o: $(SRC_PATH)/i2libisoff.c $(INCLUDE_PATH)/i2libisoff.h $(INCLUDE_PATH)/i2context.h
	$(CC) $(CFLAGS) -c $(SRC_PATH)/i2libisoff.c

lib: i2libdash.o i2libisoff.o h264_stream.o i2nalparser.o
	mkdir -p lib
	$(CC) $(LDFLAGS) -o $(LIB_PATH)/$(LIB_SHARED_NAME).$(VERSION) i2libdash.o i2libisoff.o h264_stream.o i2nalparser.o
	ar rcs $(LIB_PATH)/$(LIB_STATIC_NAME) i2libdash.o i2libisoff.o h264_stream.o i2nalparser.o

install-lib: lib
	cp -f $(INCLUDE_PATH)/*.h $(INSTALL_INCLUDE_PATH)
	cp -f $(LIB_PATH)/$(LIB_SHARED_NAME).$(VERSION) $(INSTALL_LIB_PATH)
	cp -f $(LIB_PATH)/$(LIB_STATIC_NAME) $(INSTALL_LIB_PATH)
	ln -f -s $(INSTALL_LIB_PATH)/$(LIB_SHARED_NAME).$(VERSION) $(INSTALL_LIB_PATH)/$(LIB_SHARED_NAME)
	ldconfig
testlib: lib_test_video.o lib_test_audio.o paper.o
#testlib: lib_test_video.o lib_test_audio.o
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG_V_LIB) $(TEST_PATH)/lib_test_video.o $(LIB_FLAGS)
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG_A_LIB) $(TEST_PATH)/lib_test_audio.o $(LIB_FLAGS)
	$(CC) $(CFLAGS) -o $(BIN_PATH)/$(PROG_PAPER) $(TEST_PATH)/paper.o $(LIB_FLAGS) -lrt
	mkdir -p $(TEST_DIR)/$(LIB_SEGMENT)

paper.o:  $(TEST_PATH)/paper.c
	$(CC) $(CFLAGS) -c $(TEST_PATH)/paper.c
	mv paper.o $(TEST_PATH)/

lib_test_video.o:  $(TEST_PATH)/lib_test_video.c
	$(CC) $(CFLAGS) -c $(TEST_PATH)/lib_test_video.c
	mv lib_test_video.o $(TEST_PATH)/

lib_test_audio.o:  $(TEST_PATH)/lib_test_audio.c
	$(CC) $(CFLAGS) -c $(TEST_PATH)/lib_test_audio.c
	mv lib_test_audio.o $(TEST_PATH)/

clean:
	rm -f $(BIN_PATH)/* $(TEST_PATH)/*.o $(LIB_PATH)/* ./*.o

unistall:
	rm -f $(BIN_PATH)/* $(TEST_PATH)/*.o $(LIB_PATH)/* ./*.o $(INSTALL_INCLUDE_PATH)/i2*.h $(INSTALL_INCLUDE_PATH)/h264_stream.h $(INSTALL_INCLUDE_PATH)/i2nalparser.h $(INSTALL_INCLUDE_PATH)/bs.h $(INSTALL_LIB_PATH)/$(LIB_SHARED_NAME).$(VERSION) $(INSTALL_LIB_PATH)/$(LIB_SHARED_NAME) $(INSTALL_LIB_PATH)/$(LIB_STATIC_NAME) 

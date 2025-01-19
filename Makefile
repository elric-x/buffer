CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99


LIB_TARGET = libbuffer.a
TEST_TARGET = test.buffer
ARCHIVE = libbuffer.tar

all:  $(LIB_TARGET)  $(TEST_TARGET) $(ARCHIVE)

$(LIB_TARGET): buffer.o
	ar rcs $@  buffer.o 

$(ARCHIVE):$(LIB_TARGET) buffer.h
	tar -cf $(ARCHIVE) $(LIB_TARGET) buffer.h


buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c -o $@

$(TEST_TARGET): buffer.o test.buffer.c 
	$(CC) $(CFLAGS) test.buffer.c -L. -lbuffer -o $@

clean:
	rm $(LIB_TARGET) 
	rm $(TEST_TARGET) 
	rm $(ARCHIVE) 

# Phony targets
.PHONY: all clean


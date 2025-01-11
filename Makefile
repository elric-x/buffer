CC = gcc
CFLAGS = -Wall -Wextra


LIB_TARGET = libbuffer.tar
TEST_TARGET = buffer_test

all:  $(LIB_TARGET)  $(TEST_TARGET)

$(LIB_TARGET): buffer.o
	tar -cf $@  buffer.o buffer.h


buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c -o $@

$(TEST_TARGET): buffer.o test.buffer.c 
	$(CC) $(CFLAGS) buffer.o test.buffer.c -o $@

clean:
	rm $(LIB_TARGET) 
	rm $(TEST_TARGET) 

# Phony targets
.PHONY: all clean


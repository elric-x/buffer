CC = gcc
CFLAGS = -Wall -Wextra

OBJDIR = ./obj
BINDIR = ./bin

LIB_TARGET = libbuffer.tar
TEST_TARGET = buffer_test

all: $(OBJDIR) $(LIB_TARGET)  $(TEST_TARGET)
# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIB_TARGET): $(OBJDIR)/buffer.o
	tar -cf $@ $<

$(OBJDIR)/buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c -o $@

$(TEST_TARGET): $(OBJDIR)/buffer.o test.buffer.c 
	$(CC) $(CFLAGS) $(OBJDIR)/buffer.o test.buffer.c -o $@

clean:
	rm -rf $(OBJDIR) 
	rm $(LIB_TARGET) 
	rm $(TEST_TARGET) 

# Phony targets
.PHONY: all clean


CC = gcc

csrc = $(wildcard src/*.c) \
 	   $(wildcard src/engine/*.c) \
 	   $(wildcard src/engine/util/*.c) 

obj = $(csrc:.c=.o)

odir = ./obj

LDFLAGS = -lncurses

cowbot: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog

CC = gcc

csrc = $(wildcard src/*.c) \
 	   $(wildcard src/engine/*.c) \
 	   $(wildcard src/engine/util/*.c) \
 	   $(wildcard src/engine/things/*.c) \

obj = $(csrc:.c=.o)

odir = ./obj

LDFLAGS = -lncurses

CFLAGS = -DDEBUG

dino_term: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog

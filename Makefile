CC = gcc

csrc = $(wildcard src/*.c) \
 	   $(wildcard src/engine/*.c) 

obj = $(csrc:.c=.o)

odir = ./obj

LDFLAGS = -lncurses

cowbot: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog

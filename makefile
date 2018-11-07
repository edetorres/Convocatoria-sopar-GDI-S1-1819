CC=gcc
DEPS = prog.c

all: $(DEPS)
	$(CC) -o $@ $^ 
	./$@

ncurses: convo.c
	$(CC) -o $@ $^ -lncurses
	./$@


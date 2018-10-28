CC=gcc
DEPS = prog.c

convo: $(DEPS)
	$(CC) -o $@ $^ 
	./$@
	

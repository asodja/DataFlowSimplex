CCFLAGS	:= -O3 -std=c99

all: genlp sollp


genlp: genlp.c common.o formats.o
	$(CC) $(CCFLAGS) $^ -o $@


sollp: sollp.o common.o formats.o
	$(CC) $(CCFLAGS) $^ -o $@


sollp.o: sollp.c simplex_cpu.c
	$(CC) $(CCFLAGS) -c $< -o $@


%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $< -o $@


clean:
	@rm -f genlp sollp
	@rm -f *.o


@PHONY: all clean

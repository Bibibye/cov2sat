CC=gcc
CFLAGS=-Wall -Werror -std=c99 -DNO_DEBUG -c
GRAPHFILES=K5_5.c K7_11.c C10.c C10a2.c C10a3.c Petersen.c
MAINFILE=cov2sat.c
OUTFILES=$(GRAPHFILES:.c=.out)

.PHONY: all run clean mrproper

.PRECIOUS: %.o

all: $(OUTFILES)

%.out: %.o $(MAINFILE:.c=.o)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^

run: all
	@for i in $(OUTFILES) ; do echo "- $$i" && ./solver.sh ./$$i ; done

clean:
	$(RM) *.o
	$(RM) *~

mrproper: clean
	$(RM) $(OUTFILES)

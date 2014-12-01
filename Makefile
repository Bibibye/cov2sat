CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c
ifeq ($(DEBUG), yes)
	CFLAGS+= -g
else
	CFLAGS+= -DNO_DEBUG -O2
endif
EASY_GRAPHFILES= K5_5.c K7_11.c C10.c C10a2.c C10a3.c Petersen.c sierp23.c CP16.c
GRAPHFILES=$(EASY_GRAPHFILES) kn62.c sierp33.c CB16.c CB20.c CP20.c C20.c C24.c
MAINFILE=cov2sat.c
EASY_OUTFILES=$(EASY_GRAPHFILES:.c=.out)
OUTFILES=$(GRAPHFILES:.c=.out)

.PHONY: all run clean mrproper

.PRECIOUS: %.o

all: $(OUTFILES)

%.out: %.o $(MAINFILE:.c=.o)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^

run: all
	@for i in $(EASY_OUTFILES) ; do echo -n "- $$i : " && ./solver.sh ./$$i ; done

run_difficult: all
	@for i in $(OUTFILES) ; do echo -n "- $$i : " && ./solver.sh ./$$i ; done

clean:
	$(RM) *.o
	$(RM) *~
	$(RM) \#*

mrproper: clean
	$(RM) $(OUTFILES)

CC = gcc
CFLAGS = -O2

TARGETS = ffd_bounds

all: $(TARGETS)

ffd_bounds: ffd_bounds.c
	${CC} ${CFLAGS} -o ffd_bounds ffd_bounds.c

.c.o:
	${CC} ${CFLAGS} -Wall -c $*.c

clean:
	rm -f *.o $(TARGETS)

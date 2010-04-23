CC = gcc
CFLAGS = -O2

TARGETS = deform

SRCC = $(wildcard *.c)
OBJC = $(patsubst %.c,%.o,$(SRCC))
HDRS = $(wildcard *.h)

all: $(TARGETS)

deform: $(OBJC)
	${CC} -o deform $(OBJC) -lm

$(OBJC): $(HDRS)

.c.o:
	${CC} ${CFLAGS} -Wall -c $*.c

clean:
	rm -f *.o $(TARGETS)

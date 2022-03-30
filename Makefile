OBJS=	norm.o
CFLAGS=	-O2

all:	norm

norm:	$(OBJS)
	$(CC) $(CFLAGS) -o norm $(OBJS)

clean:
	rm -f norm $(OBJS)

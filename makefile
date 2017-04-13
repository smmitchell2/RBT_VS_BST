OBJS = bstrees.o bst.o vbst.o rbt.o sll.o queue.o integer.o real.o string.o comparator.o read.o scanner.o -o bstrees
OOPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g

all : bstrees

bstrees : bstrees.o bst.o vbst.o rbt.o sll.o queue.o integer.o real.o string.o comparator.o read.o scanner.o
	gcc $(LOPTS) $(OBJS)

bstrees.o : bstrees.c bst.h vbst.h rbt.h
	gcc $(OOPTS) bstrees.c

bst.o : bst.c bst.h
	gcc $(OOPTS) bst.c

vbst.o : vbst.c vbst.h
	gcc $(OOPTS) vbst.c

rbt.o : rbt.c rbt.h
	gcc $(OOPTS) rbt.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

comparator.o : comparator.c comparator.h
	gcc $(OOPTS) comparator.c

read.o : read.c read.h
	gcc $(OOPTS) read.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

test : bstrees
	./bstrees -v empty display

clean :
	rm -f bstrees.o bst.o vbst.o rbt.o sll.o queue.o integer.o real.o string.o comparator.o read.o scanner.o bstrees

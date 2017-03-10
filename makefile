OBJS = scanner.o sll.o comparator.o  queue.o bst.o vbst.o rbt.o bstrees.o
OOPTS = -Wall -std=c99 -c -g
LOOPTS = -Wall -std=c99 -g

bstrees : $(OBJS)
	gcc $(LOOPTS) $(OBJS) -o bstrees

bstrees.o : bstrees.c scanner.h comparator.h dll.h queue.h vbst.h bst.h rbt.h
	gcc $(OOPTS) bstrees.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

comparator.o: comparator.c comparator.h integer.h real.h
	gcc $(OOPTS) comparator.c

bst.o: bst.c queue.h comparator.h
	gcc $(OOPTS) bst.c

vbst.o: vbst.c queue.h comparator.h bst.h
	gcc $(OOPTS) vbst.c

rbt.o: rbt.c queue.h comparator.h bst.h
	gcc $(OOPTS) rbt.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

test :
	#testing#
	bstrees
	@echo
	@echo
	
clean   :
	rm -f *.o sqsort

OBJS = scanner.o integer.o real.o sll.o dll.o comparator.o  queue.o stack.o sqsort.o
OOPTS = -Wall -std=c99 -c -g
LOOPTS = -Wall -std=c99 -g

sqsort : $(OBJS)
	gcc $(LOOPTS) $(OBJS) -o sqsort

sqsort.o : sqsort.c integer.h real.h scanner.h comparator.h sll.h dll.h stack.h queue.h
	gcc $(OOPTS) sqsort.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

stack.o : stack.c stack.h dll.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

comparator.o: comparator.c comparator.h integer.h real.h
	gcc $(OOPTS) comparator.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

test :
	#testing integer file read#
	sqsort -d num
	@echo
	@echo
	
clean   :
	rm -f *.o sqsort

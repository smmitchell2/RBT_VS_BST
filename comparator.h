#ifndef __COMPARATOR_INCLUDED__
#define __COMPARATOR_INCLUDED__

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);

extern int stringComparator(void *a, void *b);

#endif

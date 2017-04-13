#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "bst.h"
#include "vbst.h"
#include "rbt.h"

#ifndef __READ_INCLUDED__
#define __READ_INCLUDED__

extern void readFileVBST (FILE *,vbst*);
extern void readFileRBT (FILE *,rbt *);
extern void readCommandsVBST (FILE *,FILE *,vbst*);
extern void readCommandsRBT (FILE *,FILE*,rbt*);
extern char *obtainString(FILE *);
extern void cleanString (char *);

#endif

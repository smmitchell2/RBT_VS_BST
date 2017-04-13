#include <stdio.h>
#include <string.h>
#include "read.h"
#include "comparator.h"


int main (int argc, char **argv) {
    FILE *fpCorpus = NULL, *fpCommands = NULL, *fpOutfile = NULL;
    if (argc < 2 || argc > 5)
        fprintf(stderr,"Error: Improper number of commands!\n");
    //open corpus
    fpCorpus = fopen(argv[2], "r");
    //errror checking
    if (fpCorpus == NULL)
        fprintf(stderr,"Error: %s file didn't open!\n",argv[2]);
    //open commands
    fpCommands = fopen(argv[3], "r");
    //errror checking
    if (fpCommands == NULL)
        fprintf(stderr,"Error: %s file didn't open!\n",argv[3]);
    //open output file if one is given
    if (argc == 5) {
        fpOutfile = fopen(argv[4], "w");
        if (fpOutfile == NULL)
            fprintf(stderr,"Error: %s file didn't open!\n",argv[4]);
    }
    //set it to stdout
    else {
        fpOutfile =  stdout;
    }
    if (strcmp(argv[1],"-v") == 0) {
        vbst *v = newVBST(displayString,stringComparator);
        readFileVBST(fpCorpus,v);
        readCommandsVBST(fpCommands,fpOutfile,v);
    }
    else if (strcmp(argv[1],"-r") == 0) {
        rbt *r = newRBT(displayString,stringComparator);
        readFileRBT(fpCorpus,r);
        readCommandsRBT(fpCommands,fpOutfile,r);
    }
    else
        fprintf(stderr,"Error: %s is not a valid command!\n",argv[1]);
    if(fpCorpus != NULL)
        fclose(fpCorpus);
    if(fpCommands != NULL)
        fclose(fpCommands);
    if(fpOutfile != NULL)
        fclose(fpOutfile);
    return 0;
}
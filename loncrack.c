#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "color_set.h"

#define BOOL        unsigned char
#define TRUE        1
#define FALSE       0

void usage (char * s);

int 
main (int argc, char ** argv) {
	FILE * arq;
    char senha[75];
	char salt[25];
	char comp[100];
	char * result;

    if (argc < 2) {
        usage (argv[0]);
        exit(0);
    }

	if ( (arq = fopen (argv[1],"r") ) == NULL) {
        fprintf (stderr, "[%sERROR%s] opening the file: %s%s%s.\n", 
                T_RED, NOTHING, 
                T_RED, argv[1], 
                NOTHING);
        exit(-1);
    }
    

	


	printf ("Digite o %sHash%s completo\n", T_BLUE, NOTHING);
    fgets (comp, sizeof (comp), stdin);

	printf ("Digite o Salt\n");
	fgets (salt, sizeof(salt), stdin);

	BOOL found = FALSE;

	while (fscanf (arq, "%s", &senha) != EOF) {
        result = (char *) crypt (senha, salt);
		if (strcmp (comp,result) == 0){
		    printf ("Senha encontrada: %s%s%s \n", 
                    T_YELL, senha, NOTHING);

    		found = TRUE;

	    	return 0;

		} else {
    	    printf ("Testando.. %s%s%s\n", T_BLUE, senha, NOTHING);

		}

	}

    if(!found){
        printf ("[%sWARN%s] - Senha %snão%s encontrada ...\n",
                T_RED, NOTHING,
                T_RED, NOTHING);

	}
}

void 
usage (char * s) {
    printf ("%sUsage: %s %s<filename>%s\n", 
            T_BLUE, s,
            T_RED, NOTHING);
}

void
refresh (FILE * fp) {
    int c;
    while ( (c = getc(fp) ) != 0x0a && c != 0x0d);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *ex = malloc(sizeof(char)*64);
	strcpy(ex, "   S A  LAM   \n s d ! $ \n \0");
	char *line;
	
	/* define "\n" as delimiter */
	const char * s = "\n";
	/* get the first line */ 
	line = strtok(ex, s);
	/* walk through other tokens */
	while( line != NULL ) {
		printf( ">> %s\n", line);
		line = strtok(NULL, s);
	}
	free(ex);
    return 0;
}

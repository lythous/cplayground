#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Search in s1 and erase from s2 to the end. */
void erase_str_after(char **s1, const char * s2) {
	char * pch = strstr(*s1, s2);
	*pch ='\0';
}	


int main(void) {
	char *str = malloc(sizeof(char)*64);
	strcpy(str, "salam bar mardan x");	
	
	erase_str_after(&str, "mard");
	printf("%s\n", str);
	
	free(str);
    return 0;
}


/* OUTPUT:
 * salam bar
 */
